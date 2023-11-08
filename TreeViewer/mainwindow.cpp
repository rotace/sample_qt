#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCore>
#include <QtWidgets>
#include "common.h"
#include "makeviewdialog.h"

constexpr qint32 INDEX_ID = 0;
constexpr qint32 INDEX_PARENTID = 1;
constexpr qint32 INDEX_PRIORITY = 2;

/**
 * @brief ツリー表示の列名を設定する
 * @param w ウィジェット
 */
inline void CREATE_TREE_HEADER(QTreeWidget *w)
{
    w->setHeaderLabels(QStringList()
                       << "id"
                       << "parentId"
                       << "priority"
                       << "address"
                       << "values");
}

/**
 * @brief ツリー要素を生成する
 * @param query クエリ
 * @return ツリー要素
 */
inline QTreeWidgetItem* CREATE_TREE_ITEM(QSqlRecord record)
{
    // ツリー要素の生成
    QTreeWidgetItem *item = new QTreeWidgetItem();
    QVariant priority = record.value("priority");
    qint32 count = 0;
    item->setData(count++, Qt::DisplayRole, record.value("id"));
    item->setData(count++, Qt::DisplayRole, record.value("parentId"));
    item->setData(count++, Qt::DisplayRole, (priority.isNull() ? QVariant() : priority.toInt()));
    item->setData(count++, Qt::DisplayRole, record.value("address"));
    item->setData(count++, Qt::DisplayRole, record.value(record.count()-1));

    // ツリー要素の各種設定
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
    item->setCheckState(0, Qt::Checked);
    return item;
}

/**
 * @brief コンストラクタ
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mModel(new QSqlQueryModel(this))
{
    ui->setupUi(this);

    // ウィジェットの初期化
    ui->tableView->setModel(mModel);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
    connect(ui->pushButtonImportCsv, &QPushButton::clicked, this, &MainWindow::onPushButtonImportCsvClicked);

    // データベースの初期化
    QSqlDatabase db;
    if( QSqlDatabase::contains(mDatabaseId) ) {
        db = QSqlDatabase::database(mDatabaseId);
    }else{
        db = QSqlDatabase::addDatabase("QSQLITE", mDatabaseId);
        db.setDatabaseName(qApp->applicationName()+".db");
        db.open();
    }
}

/**
 * @brief デストラクタ
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief ファイルダイアログでCSVを選択してデータベースに読み込む
 */
void MainWindow::onPushButtonImportCsvClicked()
{
    static QDir dir(QDir::currentPath()+"/"+qApp->applicationName()+"/csv");
    QString fileName = QFileDialog::getOpenFileName(this, "Load", dir.path(), "*.csv");
    QFile file(fileName);

    if(!file.exists() || !file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        // ファイルを開くことに失敗
        qDebug() << "File Cannot Open!";
        file.close();
        return;
    }

    // 開いたファイルを記憶する
    dir = QFileInfo(file).dir();

    // CSVを読み込む
    QSqlDatabase db = QSqlDatabase::database(mDatabaseId);
    QSqlQuery query(db);
    bool isHeader = true;
    QTextStream in(&file);
    while(!in.atEnd())
    {
        if(isHeader)
        {
            // 表の作成
            QStringList sql;
            sql << "create table if not exists MainTable (";
            bool isFirst = true;
            for(auto &column : in.readLine().split(","))
            {
                sql << (isFirst ? "    " : "  , ")
                    << column
                    << "TEXT";
                isFirst = false;
            }
            sql << ")";
            if(!query.exec("drop table if exists MainTable")) PUBLISH_QUERY_ERROR(query);
            if(!query.exec(sql.join("\n"))) PUBLISH_QUERY_ERROR(query);

        }
        else
        {
            // 値の挿入
            QStringList sql;
            sql << "insert into MainTable values (";
            bool isFirst = true;
            for(auto &value : in.readLine().split(","))
            {
                sql << (isFirst ? "    " : "  , ")
                    << (value.isEmpty() ? "null" : "'"+value+"'");
                isFirst = false;
            }
            sql << ")";
            if(!query.exec(sql.join("\n"))) PUBLISH_QUERY_ERROR(query);
        }
        isHeader = false;
    }
    file.close();

    // ビューの作成
    MakeViewDialog dialog(mDatabaseId, this);

    if(dialog.exec()!=QDialog::Accepted)
    {
        // ビューの作成に失敗
        qDebug() << "Make View Failed!";
        return;
    }

    // テーブル表示を更新する
    mModel->setQuery("select * from MainView", db);

    // ツリー表示を更新する
    this->updateTreeWidget();

    qDebug() << "Load Finished!";
}

/**
 * @brief ツリー表示を更新する
 */
void MainWindow::updateTreeWidget()
{
    QList<QTreeWidgetItem*> stackItems;
    QSqlQuery query(QSqlDatabase::database(mDatabaseId));

    // ツリー表示の初期化
    ui->treeWidget->clear();
    CREATE_TREE_HEADER(ui->treeWidget);

    // スタックの先頭にルート要素を追加する
    stackItems << ui->treeWidget->invisibleRootItem();

    // アドレス順に並び替える
    if(!query.exec("select * from MainView order by address asc")) PUBLISH_QUERY_ERROR(query);

    // アドレス順にツリーを構築
    while(query.next())
    {
        // スタックの先頭が親になるまでスタックから要素を取り除く
        qint32 parentLevel = query.value("address").toString().split("/").size();
        while(parentLevel < stackItems.count()) stackItems.removeLast();

        // スタックには常にルート要素が存在する
        Q_ASSERT(stackItems.count()>0);

        // 生成した要素を親レベルに追加＆スタックの先頭に追加
        QTreeWidgetItem *item = CREATE_TREE_ITEM(query.record());
        stackItems.last()->addChild(item);
        stackItems << item;
    }

    // 優先度順に並び替える
    ui->treeWidget->sortItems(INDEX_PRIORITY, Qt::AscendingOrder);
}


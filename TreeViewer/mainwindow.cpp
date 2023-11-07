#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCore>
#include <QtWidgets>
#include "common.h"
#include "makeviewdialog.h"

/**
 * @brief ツリー要素を生成する
 * @param items 表示データ
 * @return ツリー要素
 */
inline QTreeWidgetItem* CREATE_TREE_ITEM(QStringList items)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(items);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
    item->setCheckState(3, Qt::Checked);
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
    QString oldAddress;
    QString curAddress;
    QStringList indentations;
    QList<QTreeWidgetItem*> parents;
    if(!query.exec("select * from MainView order by address asc")) PUBLISH_QUERY_ERROR(query);
    while(query.next())
    {
        oldAddress = curAddress;
        curAddress = query.value("address").toString();
        QVariant id = query.value("id");
        QVariant parentId = query.value("parentId");
        QStringList values;
        for(qint32 i=2; i<query.record().count(); i++)
            values << query.value(i).toString();

        QStringList displays = QStringList()
                << id.toString()
                << parentId.toString()
                << curAddress
                << values.join(",");

        while(!indentations.isEmpty())
        {
            if(curAddress.startsWith(indentations.last()))
            {
                QTreeWidgetItem *item = CREATE_TREE_ITEM(displays);
                parents.last()->addChild(item);
                indentations << curAddress;
                parents << item;
                break;
            }
            else
            {
                indentations.removeLast();
                parents.removeLast();
            }
        }

        if(indentations.isEmpty())
        {
            QTreeWidgetItem *item = CREATE_TREE_ITEM(displays);
            ui->treeWidget->addTopLevelItem(item);
            indentations << curAddress;
            parents << item;
        }
    }
    qDebug() << "Load Finished!";
}


#include "makeviewdialog.h"
#include "ui_makeviewdialog.h"

#include <QtSql>
#include "common.h"

/**
 * @brief コンストラクタ
 * @param databaseId データベースID
 * @param parent
 */
MakeViewDialog::MakeViewDialog(QString databaseId, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MakeViewDialog)
    , mDatabaseId(databaseId)
{
    ui->setupUi(this);

    // ウィジェットの初期化
    QSqlQuery query(QSqlDatabase::database(mDatabaseId));
    if(!query.exec("PRAGMA table_info('MainTable')")) PUBLISH_QUERY_ERROR(query);
    while(query.next())
    {
        ui->comboBoxId->addItem(query.value("name").toString());
        ui->comboBoxParentId->addItem(query.value("name").toString());
    }

    connect(this, &QDialog::accepted, this, [=](){
        QSqlQuery query(QSqlDatabase::database(mDatabaseId));
        QStringList sql;

        // 隣接リストビューの作成　（隣接リストとは、グラフ理論における頂点または辺をリストで表現したものである。）
        sql.clear();
        sql << "create view AdjacencyList as"
            << "select"
            << ui->comboBoxId->currentText() << "as id,"
            << ui->comboBoxParentId->currentText() << "as parentId"
            << "from MainTable";

        if(!query.exec("drop view if exists AdjacencyList")) PUBLISH_QUERY_ERROR(query);
        if(!query.exec(sql.join("\n"))) PUBLISH_QUERY_ERROR(query);

        // アドレスリストビューの作成　（アドレスとは、ルート要素までのIDを連ねて表現したものである。）
        // Non Recursive Section／非再帰項　…　最初に実行され、Tmpテーブルに格納する。
        //     Recursive Section／再帰項　　…　２回目以降に実行され、Tmpテーブルに格納する。Tmpテーブルのレコードがなくなるまで再帰的に実行される。
        //        Result Section／結果項　　…　最後に実行される。
        sql.clear();
        sql << "create view AddressList as"
            << ""
            << "with recursive Tmp(id, rootId, address) as ("
            << ""
            << "-- Non Recursive Section"
            << "select id, parentId, cast(id as text) from AdjacencyList"
            << ""
            << "union all"
            << ""
            << "-- Recursive Section"
            << "select Tmp.id, AdjacencyList.parentId, AdjacencyList.id || '/' || Tmp.address from AdjacencyList, Tmp"
            << "where AdjacencyList.id = Tmp.rootId"
            << ")"
            << ""
            << "-- Result Section"
            << "select id, address from Tmp where rootId is null"
            << "";
        if(!query.exec("drop view if exists AddressList")) PUBLISH_QUERY_ERROR(query);
        if(!query.exec(sql.join("\n"))) PUBLISH_QUERY_ERROR(query);

        // 表示ビューの作成
        sql.clear();
        sql << "create view MainView as"
            << "select AdjacencyList.*, AddressList.address, MainTable.* from MainTable"
            << "left join AdjacencyList"
            << "on" << QString("MainTable.%1").arg(ui->comboBoxId->currentText()) << "= AdjacencyList.id"
            << "left join AddressList"
            << "on" << QString("MainTable.%1").arg(ui->comboBoxId->currentText()) << "= AddressList.id"
            << "order by AddressList.address asc";
        if(!query.exec("drop view if exists MainView")) PUBLISH_QUERY_ERROR(query);
        if(!query.exec(sql.join("\n"))) PUBLISH_QUERY_ERROR(query);
    });
}

/**
 * @brief デストラクタ
 */
MakeViewDialog::~MakeViewDialog()
{
    delete ui;
}

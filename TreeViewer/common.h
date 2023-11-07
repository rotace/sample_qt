#pragma once

#include <QtSql>
#define PUBLISH_DB_ERROR(s) PRINT_DB_ERROR(s,__FILE__,__LINE__,__FUNCTION__)
#define PUBLISH_QUERY_ERROR(s) PRINT_QUERY_ERROR(s,__FILE__,__LINE__,__FUNCTION__)

/**
 * @brief クエリをログ出力する
 * @param query クエリ
 */
inline void PRINT_QUERY(QSqlQuery &query)
{
    qWarning().noquote() << "----(query)----";
    qint32 count = 1;
    const auto &l = query.lastQuery().split("\n");
    for(const auto &s:l) qWarning().noquote() << QString("%1").arg(count++,3) << ":" << s;
}

/**
 * @brief バインド値をログ出力する
 * @param query クエリ
 */
inline void PRINT_BOUND_VALUE(QSqlQuery &query)
{
    qWarning().noquote() << "----(value)----";
    QMapIterator<QString, QVariant> i(query.boundValues());
    while(i.hasNext()) {
        i.next();
        qWarning().noquote() << i.key() << i.value();
    }
}

/**
 * @brief データベースのエラーをログ出力する
 * @param db データベース
 * @param file エラーが発生したファイル
 * @param line エラーが発生した行数
 * @param func エラーが発生した関数
 */
inline void PRINT_DB_ERROR(QSqlDatabase &db, const char *file, int line, const char *func)
{
    qWarning().noquote() << "--!!!!!!!!!!!!!!!!!!! SQL ERROR !!!!!!!!!!!!!!!!!!!!";
    qWarning().noquote().nospace() << file << ":" << line << ":" << func <<"()";
    qWarning().noquote() << db.lastError().driverText();
    const auto &l = db.lastError().databaseText().split("\n");
    for(const auto &s:l) qWarning().noquote() << s;
    qWarning().noquote() << "--!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
}

/**
 * @brief クエリのエラーをログ出力する
 * @param query クエリ
 * @param file エラーが発生したファイル
 * @param line エラーが発生した行数
 * @param func エラーが発生した関数
 */
inline void PRINT_QUERY_ERROR(QSqlQuery &query, const char *file, int line, const char *func)
{
    qWarning().noquote() << "--!!!!!!!!!!!!!!!!!!! SQL ERROR !!!!!!!!!!!!!!!!!!!!";
    qWarning().noquote().nospace() << file << ":" << line << ":" << func <<"()";
    qWarning().noquote() << query.lastError().driverText();
    const auto &l = query.lastError().databaseText().split("\n");
    for(auto &s:l) qWarning().noquote() << s;
    PRINT_QUERY(query);
    PRINT_BOUND_VALUE(query);
    qWarning().noquote() << "--!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
}

/**
 * @brief クエリ結果をログ出力する
 * @param query クエリ
 */
inline void PRINT_QUERY_RESULT(QSqlQuery &query)
{
    qWarning().noquote() << "----(result)----";
    while(query.next()) {
        QSqlRecord record = query.record();
        qint32 n = record.count();
        QStringList list;
        for(qint32 i=0; i<n; i++) list << query.value(i).toString();
        qWarning() << list.join(", ");
    }
}

/**
 * @brief （WITH句中の）サブクエリ結果をログ出力する
 * @param query クエリ
 * @param subName 出力するサブクエリ名
 * @param with WITH句
 */
inline void PRINT_SUBQUERY_RESULT(QSqlQuery &query, QString subName, QString with)
{
    with += QString("\n select * from %1").arg(subName);
    if(!query.exec(with)) PUBLISH_QUERY_ERROR(query);
    PRINT_QUERY_RESULT(query);
}

/**
 * @brief コンボボックスに列挙型の要素を表示する
 * @param c コンボボックス
 * @param e 列挙型のメタデータ
 */
inline void REGISTER_COMBOBOX(QComboBox* c, QMetaEnum e)
{
    for(qint32 index=0; index<e.keyCount(); index++) {
        c->addItem(e.key(index), e.value(index));
    }
}

/**
 * @brief 列挙型の値を文字列に変換する
 * @param value 列挙型の値
 * @return 列挙型の文字列
 */
template<typename QENUM>
inline QString VALUE_TO_KEY(qint32 value)
{
    return QMetaEnum::fromType<QENUM>().valueToKey(value);
}


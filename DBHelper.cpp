#include "DBHelper.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
DBHelper* DBHelper::intance = 0;
DBHelper* DBHelper::getIntance()
{
       if(intance == 0)
       {
           intance = new DBHelper();
       }
       return intance;
}
void DBHelper::createConnect()
{
    db.setDatabaseName("chat.db");
    if(db.open())
    {
        qDebug() << "database succeeded to open";
    }
    else
    {
        qDebug() << "database failed to open";
    }
    QSqlQuery query(db);
    QString create_sql = "create table if not exists tb_user (id int primary key ,username text not null, "
                         "nickname text not null, passwd text not null,phonenumber text not null);";
    query.prepare(create_sql);
    bool queryret = query.exec();
    if(!queryret)
    {
        qDebug() << "Error: Fail to create table." << query.lastError();
    }
    else
    {
        qDebug() << "Table created or  table  exist!";
    }
    qDebug()<<"建库建表:"<<queryret;
}
void DBHelper::destoryConnect()
{
    db.close();
    db.removeDatabase("chat.db");
}

DBHelper::DBHelper()
{
    db = QSqlDatabase::addDatabase("QSQLITE");

}

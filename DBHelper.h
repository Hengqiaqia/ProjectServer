#ifndef DBHELPER_H
#define DBHELPER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class DBHelper
{
public:
    static DBHelper* getIntance();
    void createConnect();
    void destoryConnect();


private:
    QSqlDatabase db;
    static DBHelper* intance;
    DBHelper();
};

#endif // DBHELPER_H

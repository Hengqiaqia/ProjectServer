#ifndef DBHELPER_H
#define DBHELPER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "Utils.h"
class DBHelper
{
public:
    static DBHelper* getIntance();
    void createConnect();
    void destoryConnect();

protected:

private:
    QSqlDatabase db;
    static DBHelper* intance;
    DBHelper();

};

#endif // DBHELPER_H

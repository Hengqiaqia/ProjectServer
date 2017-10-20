#ifndef UTILS_H
#define UTILS_H
#include <QString>
#include <QTime>
#include <QDebug>
#include <QSqlQuery>
#include <QMutexLocker>
#include "DBHelper.h"

class Utils
{
public:
    Utils();
    QString generateRandomNumber();
    int IsValid( QSqlQuery query,const QString& tableName, const QString& fieldName);
};

#endif // UTILS_H

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
    //生成随机的数字 作为账号
    QString generateRandomNumber(int n);
    int IsValid( QSqlQuery query,const QString& tableName, const QString& fieldName);
//    QString getVerification();//生成4位数字 作为手机验证码
    QString createUserTable();//创建用户表 语句
    QString createPhoneVerTable();//创建手机验证码表  语句
    bool ExecSQL(QSqlDatabase db,QString createSQL);//执行创建语句

};

#endif // UTILS_H

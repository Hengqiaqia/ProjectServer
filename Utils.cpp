#include "Utils.h"
#include <QDebug>
#include <QMutexLocker>
#include <QSqlQuery>
#include <QSqlRecord>
Utils::Utils()
{

}
//生成账号 循环几次
QString Utils::generateRandomNumber(int n)
{
    QString str = "";
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for(int i=0; i<n; i++)
    {
        int test =qrand()%10;
        //qDebug()<<test;
        str +=QString::number(test);
    }
    qDebug()<<"获得的随机数："<<str;
    return str;
}
// 字段和表是否存在，1表示存在，0表示表不存在，-1表示字段不存在,-2表示系统错误
int Utils::IsValid( QSqlQuery query,const QString& tableName, const QString& fieldName)
{
    QString strSql = QString("SELECT * FROM SQLITE_MASTER WHERE TYPE='table' AND NAME='%1'").arg(tableName);
    if (query.exec(strSql))
    {
        if (query.next())//表存在
        {
            strSql = QString("SELECT * FROM %2").arg(tableName);
            if (query.exec(strSql))
            {
                QSqlRecord record = query.record();
                int index = record.indexOf(fieldName);
                if (index == -1)
                {
                    return -1;
                }
                else
                {
                    return 1;
                }
            }
            else
            {
                qDebug()<<__FUNCTION__<<"sql:"<<strSql<<",lastError:"<<query.lastError().text();
                return -2;
            }
        }
        else//表不存在
        {
            return 0;
        }
    }
    else
    {
        qDebug()<<__FUNCTION__<<"sql:"<<strSql<<",lastError:"<<query.lastError().text();
        return -2;
    }

}
//创建用户表格
QString Utils::createUserTable()
{
    QString create_sql = "create table if not exists tb_user (id int primary key ,username text not null, "
                         "nickname text not null, passwd text not null,phonenumber text not null);";
    return create_sql;
}
QString Utils::createOnLineUserTable()
{
    QString create_sql = "create table if not exists tb_onlineuser (id int primary key ,username text not null, "
                         "nickname text, passwd text,phonenumber text);";
    return create_sql;
}
//创建验证码表格
QString Utils::createPhoneVerTable()
{
    QString create_sql = "create table if not exists tb_verify (id int primary key ,username text not null, "
                         "phonenumber text not null,poneverify text not null,sendflag integer default(0));";

    return create_sql;
}
//执行结果
bool Utils::ExecSQL(QSqlDatabase db, QString createSQL)
{
    QSqlQuery query(db);
    query.prepare(createSQL);
    bool queryret = query.exec();
    if(!queryret)
    {
        qDebug() << "Error: 创建表失败." << query.lastError();
    }
    else
    {
        qDebug() << "创建表或表存在；";
    }
    qDebug()<<"建表:"<<queryret;
    return queryret;
}
////生成验证码
//QString Utils::getVerification()
//{
//    QString ret = "";
//    for(int i = 0; i < 4; i++)
//    {
//        int c = (qrand() % 2) ? '0' : '9';
//        ret += static_cast<QChar>(c + qrand() % 8);
//    }
//    qDebug()<<"手机验证码："<<ret;
//    return ret;
//}

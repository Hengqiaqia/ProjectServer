#include "Utils.h"
#include <QDebug>
#include <QMutexLocker>
#include <QSqlQuery>
#include <QSqlRecord>
Utils::Utils()
{

}
//生成账号 循环几次
QString Utils::generateRandomNumber()
{
    QString str = "";
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for(int i=0; i<3; i++)
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

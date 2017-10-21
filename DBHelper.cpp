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
     Utils utils;
    db.setDatabaseName("chat.db");
    if(db.open())
    {
        qDebug() << "database succeeded to open";
    }
    else
    {
        qDebug() << "database failed to open";
    }
   bool c_user = utils.ExecSQL(db,utils.createUserTable());
   if(c_user)
   {
       qDebug()<<"用户表创建成功";
   }else{
       qDebug()<<"用户表创建失败";
   }
//   bool c_verification = utils.ExecSQL(db,utils.createPhoneVerTable());
//   if(c_verification)
//   {
//       qDebug()<<"验证码表创建成功";
//   }else{
//       qDebug()<<"验证码表创建失败";
//   }
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

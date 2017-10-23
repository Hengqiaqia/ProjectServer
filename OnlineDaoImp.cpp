#include "OnlineDaoImp.h"
#include<QSqlQuery>
#include<QSqlError>
#include<QDebug>

OnlineDaoImp::OnlineDaoImp()
{

}

bool OnlineDaoImp::addOnline(QString &name)
{
    DBHelper *helper = DBHelper::getIntance();
    helper->createConnect();
    QSqlQuery query;
    query.prepare("insert into tb_onlineuser(username)values(:name);");
    query.bindValue(":name",name);
    bool ret = query.exec();
    if(ret == false){
        const QSqlError& error = query.lastError();
        qDebug() << error.text();
        helper->destoryConnect();
        return false;
    }
    helper->destoryConnect();
    return true;
}

char* OnlineDaoImp::findOnline(QString& name)
{
    DBHelper *helper = DBHelper::getIntance();
    helper->createConnect();
    QSqlQuery query;
    query.prepare("select username from tb_onlineuser where username=:name;");
    query.bindValue(":name",name);
    query.exec();
    while(query.next()){
        QString username = query.value(0).toString();
        if(username == name){
            static char *pname = username.toLocal8Bit().data();
            helper->destoryConnect();
            return pname;
        }
    }
    helper->destoryConnect();
    return NULL;
}

bool OnlineDaoImp::delOnline(QString& name)
{
    DBHelper *helper = DBHelper::getIntance();
    helper->createConnect();
    QSqlQuery query;
    query.prepare("delete from tb_onlineuser where username = :name;");
    query.bindValue(":name", name);
    bool ret = query.exec();
    if(ret == false){
        const QSqlError& error = query.lastError();
        qDebug() << error.text();
        helper->destoryConnect();
        return false;
    }
    helper->destoryConnect();
    return true;
}

vector<QString> OnlineDaoImp::selectOnline()
{
    DBHelper *helper = DBHelper::getIntance();
    helper->createConnect();
    QSqlQuery query;
    query.exec("select * from tb_onlineuser;");
    while(query.next()){
        QString username = query.value(0).toString();
        onlines.push_back(username);
    }
    helper->destoryConnect();
    return onlines;
}

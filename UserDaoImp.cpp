#include "UserDaoImp.h"
#include "DBHelper.h"

UserDaoImp::UserDaoImp()
{

}

QString UserDaoImp::insertUser(const User &user)
{
    Utils utils;
    QString username = utils.generateRandomNumber();//注册成功返回用户名
    DBHelper* helper = DBHelper::getIntance();
    helper->createConnect();
    QSqlQuery query;
     bool ret =false;
    if(user.getPhonenumber()!=NULL)
    {
        query.prepare("select * from tb_user where phonenumber=:phonenumber ");
        query.bindValue(":phonenumber",user.getPhonenumber());
        ret = query.exec();
        bool queryflag = (!query.next());
         qDebug()<<"查询："<<user.getPhonenumber()<<query.next();
        if(!queryflag)
        {
            qDebug()<<"queryflag:"<<queryflag;
           return "1";//1是手机号存在
        }else{
            QString insterSQL = "insert into tb_user (nickname,passwd,phonenumber,username) "
                                "values (:nickname,:passwd,:phonenumber,:username);";
            query.prepare(insterSQL);
            // query.bindValue(":id",user.getId());
            query.bindValue(":nickname",user.getNickname() );
            query.bindValue(":passwd",user.getPasswd());
            query.bindValue(":phonenumber",user.getPhonenumber());
            query.bindValue(":username",username);
            ret = query.exec();
            if(ret==false)
            {
                const QSqlError& error = query.lastError();
                qDebug()<<"UserDaoImp:"<<error.text();
                username = "";//后期根据这个username 判断，所以插入失败 username 是空的
            }
        }

    }

    helper->destoryConnect();
    qDebug()<<"add username:"<<username;
    return username;
}

vector<User> UserDaoImp::selectAllUser()
{
    DBHelper* helper = DBHelper::getIntance();
    vector<User> users;
    helper->createConnect();
    QSqlQuery query;
    query.exec("select id,username,nickname,passwd,phonenumber from tb_user;");
    while(query.next())
    {
        int id =query.value(0).toInt();
        QString username = query.value(1).toString();
        QString nickname = query.value(2).toString();
        QString passwd = query.value(3).toString();
        QString phonenumber = query.value(4).toString();
        User user(nickname,passwd,phonenumber,username);
        users.push_back(user);
    }
    helper->destoryConnect();
    return users;
}
//删除只能根据用户名 手机号删除
bool UserDaoImp::deleteSUser(const User &user)
{
    DBHelper* helper = DBHelper::getIntance();
    helper->createConnect();
    QSqlQuery query;
    QString sql=NULL;
    bool ret = false,execret = false,reslut = false;
    if(user.getUsername()!=NULL)
    {
        sql = "select id,username,nickname,passwd,phonenumber from tb_user where username=:username ";
        query.prepare(sql);
        query.bindValue(":username",user.getUsername());
        ret = query.exec();
        if(!query.next())
        {
            return false;
        }else{
            if(!user.getUsername().isEmpty()&&!user.getPhonenumber().isEmpty()&&!user.getNickname().isEmpty())
            {

                sql = "delete from tb_user where username=:username and nickname=:nickname and phonenumber=:phonenumber;";
                query.prepare(sql);
                query.bindValue(":username",user.getUsername());
                query.bindValue(":nickname",user.getNickname());
                query.bindValue(":phonenumber",user.getPhonenumber());
                execret = true;

            }
            else if(!user.getUsername().isEmpty()&&!user.getNickname().isEmpty())
            {

                sql = "delete from tb_user where username=:username and nickname=:nickname;";
                query.prepare(sql);
                query.bindValue(":username",user.getUsername());
                query.bindValue(":nickname",user.getNickname());
                execret = true;

            } else if(!user.getUsername().isEmpty()&&!user.getPhonenumber().isEmpty())
            {
                sql = "delete from tb_user where username=:username and phonenumber=:phonenumber;";
                query.prepare(sql);
                query.bindValue(":username",user.getUsername());
                query.bindValue(":phonenumber",user.getPhonenumber());
                execret = true;
            } else if(!user.getUsername().isEmpty())
            {
                sql = "delete from tb_user where username=:username";
                query.prepare(sql);
                query.bindValue(":username",user.getUsername());
                execret = true;
            }
        }

    }
    ret = query.exec();
    if(ret==false)
    {
        const QSqlError& error = query.lastError();
        qDebug()<<error.text();
    }
    reslut = ret && execret;
    qDebug()<<"del result:"<<reslut;
    helper->destoryConnect();
    return reslut;
}

bool UserDaoImp::updateUser(const User &user)
{
    DBHelper* helper = DBHelper::getIntance();
    helper->createConnect();
    QSqlQuery query;
    QString sql=NULL;
    bool ret = false,execret = false,reslut = false;
    if(user.getUsername()!=NULL)
    {
        sql = "select id,username,nickname,passwd,phonenumber from tb_user where username=:username ";
        query.prepare(sql);
        query.bindValue(":username",user.getUsername());
        ret = query.exec();
        if(!ret)
        {
            return false;
        }else{
            if(!user.getUsername().isEmpty()&&!user.getPhonenumber().isEmpty()&&!user.getNickname().isEmpty())
            {

                sql = "update tb_user set nickname=:nickname,phonenumber=:phonenumber where username=:username;";
                query.prepare(sql);
                query.bindValue(":username",user.getUsername());
                query.bindValue(":nickname",user.getNickname());
                query.bindValue(":phonenumber",user.getPhonenumber());
                execret = true;

            }
            else if(!user.getUsername().isEmpty()&&!user.getNickname().isEmpty())
            {

                sql = "update tb_user set nickname=:nickname where username=:username;";
                query.prepare(sql);
                query.bindValue(":username",user.getUsername());
                query.bindValue(":nickname",user.getNickname());
                execret = true;

            } else if(!user.getUsername().isEmpty()&&!user.getPhonenumber().isEmpty())
            {
                sql = "update tb_user set phonenumber=:phonenumber where username=:username;";
                query.prepare(sql);
                query.bindValue(":username",user.getUsername());
                query.bindValue(":phonenumber",user.getPhonenumber());
                execret = true;
            }
        }

    }
    ret = query.exec();
    if(ret==false)
    {
        const QSqlError& error = query.lastError();
        qDebug()<<error.text();
    }
    reslut = ret && execret;
    qDebug()<<"update result:"<<reslut;
    helper->destoryConnect();
    return reslut;
}

#if 1
vector<User> UserDaoImp::selectUser(const User &user)
{
    DBHelper* helper = DBHelper::getIntance();
    vector<User> users;
    helper->createConnect();
    qDebug()<<"141 username:"<<user.getUsername();
    qDebug()<<"143 passwd:"<<user.getPasswd();
    QSqlQuery query;
    query.prepare("select id,username,nickname,passwd,phonenumber from tb_user "
                  "where username=:username and passwd=:passwd;");
    query.bindValue(":username",user.getUsername());
    query.bindValue(":passwd",user.getPasswd());
    bool ret= query.exec();
    if(ret)
    {
        while(query.next())
        {
            int id =query.value(0).toInt();
            QString username = query.value(1).toString();
            QString nickname = query.value(2).toString();
            QString passwd = query.value(3).toString();
            QString phonenumber = query.value(4).toString();
            qDebug()<<"查询单个用户：id:"<<id<<"，username:"<<username<<"，nickname:"<<nickname<<
                      "，passwd:"<<passwd<<"，phonenumber:"<<phonenumber;
            User usera(nickname,passwd,phonenumber,username);
            users.push_back(usera);
        }
    }
    helper->destoryConnect();
    return users;

}
#endif

bool UserDaoImp::updateUserInfo(const User &user)
{
    DBHelper* helper = DBHelper::getIntance();
    helper->createConnect();
    QSqlQuery query;
    Utils utils;
    bool ret = false,reslut = false,  execret = false;
    int clomun = utils.IsValid(query,"tb_user","headimg");
    if(clomun==-1||clomun==0)
    {
        query.exec("alter table tb_user add head_img text;");
    }
    else if(clomun == 1)
    {
        qDebug()<<"字段存在";


        QString sql=NULL;
        bool ret = false,execret = false,reslut = false;
        if(user.getUsername()!=NULL)
        {
            sql = "select id,username,nickname,passwd,phonenumber from tb_user where username=:username ";
            query.prepare(sql);
            query.bindValue(":username",user.getUsername());
            ret = query.exec();
            if(!ret)
            {
                return false;
            }else{
                if(!user.getUsername().isEmpty()&&!user.getPhonenumber().isEmpty()&&!user.getNickname().isEmpty())
                {

                    sql = "update tb_user set nickname=:nickname,phonenumber=:phonenumber where username=:username;";
                    query.prepare(sql);
                    query.bindValue(":username",user.getUsername());
                    query.bindValue(":nickname",user.getNickname());
                    query.bindValue(":phonenumber",user.getPhonenumber());
                    execret = true;

                }
                else if(!user.getUsername().isEmpty()&&!user.getNickname().isEmpty())
                {

                    sql = "update tb_user set nickname=:nickname where username=:username;";
                    query.prepare(sql);
                    query.bindValue(":username",user.getUsername());
                    query.bindValue(":nickname",user.getNickname());
                    execret = true;

                } else if(!user.getUsername().isEmpty()&&!user.getPhonenumber().isEmpty())
                {
                    sql = "update tb_user set phonenumber=:phonenumber where username=:username;";
                    query.prepare(sql);
                    query.bindValue(":username",user.getUsername());
                    query.bindValue(":phonenumber",user.getPhonenumber());
                    execret = true;
                }
            }

        }
    }else if(clomun == 2)
    {
        qDebug()<<"插入字段系统错误；";
    }
    ret = query.exec();
    if(ret==false)
    {
        const QSqlError& error = query.lastError();
        qDebug()<<error.text();
    }
    reslut = ret && execret;
    qDebug()<<"update result:"<<reslut;
    helper->destoryConnect();
    return reslut;
}

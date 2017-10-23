#include "UserDaoImp.h"
#include "DBHelper.h"

UserDaoImp::UserDaoImp()
{

}

QString UserDaoImp::insertUser(const User &user)
{
    QString username = utils.generateRandomNumber(3);//注册成功返回用户名
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

QString UserDaoImp::updateUser(const User &user)
{
    DBHelper* helper = DBHelper::getIntance();
    helper->createConnect();
    QSqlQuery query;
    QString sql=NULL;
    QString msg = "";
    bool ret = false,execret = false,reslut = false;
    user.printlf();
    if(user.getUsername()!=NULL)
    {
        sql = "select id,username,nickname,passwd,phonenumber from tb_user where username=:username ";
        query.prepare(sql);
        query.bindValue(":username",user.getUsername());
        ret = query.exec();
        if(!query.next())
        {
            msg = "没有此用户";
            return msg;
        }else{
            if(!user.getPasswd().isEmpty()&&!user.getUsername().isEmpty()&&!user.getPhonenumber().isEmpty()&&!user.getNickname().isEmpty())
            {

                sql = "update tb_user set nickname=:nickname,passwd=:passwd,phonenumber=:phonenumber where username=:username;";
                query.prepare(sql);
                query.bindValue(":username",user.getUsername());
                query.bindValue(":nickname",user.getNickname());
                query.bindValue(":phonenumber",user.getPhonenumber());
                query.bindValue(":passwd",user.getPasswd());
                execret = true;
                qDebug()<<"update result:nickname，passwd,phonenumber" ;
            }else
            if(!user.getUsername().isEmpty()&&!user.getPhonenumber().isEmpty()&&!user.getNickname().isEmpty())
            {

                sql = "update tb_user set nickname=:nickname,phonenumber=:phonenumber where username=:username;";
                query.prepare(sql);
                query.bindValue(":username",user.getUsername());
                query.bindValue(":nickname",user.getNickname());
                query.bindValue(":phonenumber",user.getPhonenumber());
                execret = true;
                qDebug()<<"update result:nickname，phonenumber" ;
            }
            else if(!user.getUsername().isEmpty()&&!user.getNickname().isEmpty())
            {

                sql = "update tb_user set nickname=:nickname where username=:username;";
                query.prepare(sql);
                query.bindValue(":username",user.getUsername());
                query.bindValue(":nickname",user.getNickname());
                execret = true;
                qDebug()<<"update result:nickname" ;
            }
            else if(!user.getUsername().isEmpty()&&!user.getPhonenumber().isEmpty()&&!user.getPasswd().isEmpty())
            {
                sql = "update tb_user set passwd =:passwd where username=:username and phonenumber=:phonenumber;";
                query.prepare(sql);
                query.bindValue(":passwd",user.getPasswd());
                query.bindValue(":username",user.getUsername());
                query.bindValue(":phonenumber",user.getPhonenumber());
                qDebug()<<"update result:passwd" ;
                execret = true;
            } else if(!user.getUsername().isEmpty()&&!user.getPhonenumber().isEmpty())
            {
                sql = "update tb_user set phonenumber=:phonenumber where username=:username;";
                query.prepare(sql);
                query.bindValue(":username",user.getUsername());
                query.bindValue(":phonenumber",user.getPhonenumber());
                execret = true;
                qDebug()<<"update result:phonenumber" ;
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
    if(reslut)
    {
        msg = "更新成功";
    }else
    {
        msg="更新失败";
    }
    helper->destoryConnect();
    return msg;
}

#if 1
vector<User> UserDaoImp::selectUser(const User &user)
{
    DBHelper* helper = DBHelper::getIntance();
    vector<User> users;
    helper->createConnect();
    qDebug()<<"select username:"<<user.getUsername()<<",select passwd:"<<user.getPasswd()<<",select phonenuber:"<<user.getPhonenumber();
    QSqlQuery query;
    query.prepare("select id,username,nickname,passwd,phonenumber from tb_user "
                  "where username=:username and passwd=:passwd or (phonenumber=:phonenumber and username=:username);");
    query.bindValue(":username",user.getUsername());
    query.bindValue(":passwd",user.getPasswd());
    query.bindValue(":phonenumber",user.getPhonenumber());
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
//增加验证码
bool UserDaoImp::insertVerifi(const User &ver)
{
    return  execverify(ver);
}
//修改验证码
bool UserDaoImp::updateVerifi(const User &ver)
{
    return execverify(ver);
}
//执行 验证码 增加修改
bool UserDaoImp::execverify(const User &ver)
{
    DBHelper* helper = DBHelper::getIntance();
    helper->createConnect();
    QSqlQuery query;
    bool ret =false;
    if(!ver.getPhonenumber().isEmpty()&&!ver.getUsername().isEmpty())
    {
        query.prepare("select * from tb_user where phonenumber=:phonenumber and username=:username;");
        query.bindValue(":phonenumber",ver.getPhonenumber());
        query.bindValue(":username",ver.getUsername());
        ret = query.exec();
        bool queryflag = (!query.next());
        qDebug()<<"查询："<<ver.getPhonenumber()<<ver.getUsername()<<",ret:"<<ret<<query.next();
        if(queryflag)
        {
            qDebug()<<"查询：不存在此用户"<<!queryflag;

            return false;//不存在此用户
        }else{
            int addcolumnver = utils.IsValid(query,"tb_user","phoneverfiy");
            int addcolumnflag = utils.IsValid(query,"tb_user","sendflag");

            if(addcolumnver==-1)//-1 是字段不存在
            {
                query.exec("ALTER TABLE tb_user ADD phoneverfiy text;");
                qDebug()<<"增加字段验证码：成功";
                addcolumnver =0 ;
            }else
            {
                qDebug()<<"增加字段验证码：失败";
            }
            if(addcolumnflag==-1)//-1 是字段不存在
            {
                query.exec("ALTER TABLE tb_user ADD sendflag integer;");
                qDebug()<<"增加字段验证码次数：成功";
                addcolumnflag =0 ;
            }else
            {
                qDebug()<<"增加字段验证码：失败";
            }
            if(addcolumnflag!=-1&&addcolumnver!=-1){
                QString insterverSQL = "update tb_user set phoneverfiy=:phoneverfiy,sendflag=:sendflag where phonenumber=:phonenumber and username=:username;";
                query.prepare(insterverSQL);

                query.bindValue(":phoneverfiy",ver.getPhoneVerify());
                query.bindValue(":phonenumber",ver.getPhonenumber());
                query.bindValue(":username",ver.getUsername());
                query.bindValue(":sendflag",ver.getSendFlag());
                QString SQLstr = "update tb_user set phoneverify="+ver.getPhoneVerify()+",sendflag="+QString::number(ver.getSendFlag())+
                        " where phonenumber="+ver.getPhonenumber()+" and username="+ver.getUsername()+";";
                qDebug()<<SQLstr;
                ret = query.exec();
                if(ret==false)
                {
                    const QSqlError& error = query.lastError();
                    qDebug()<<"UserDaoImp insert verify:"<<error.text();
                }
            }else
            {
                ret = false;
                qDebug()<<"增加验证码字段失败";
            }
        }
    }
    helper->destoryConnect();
    return ret;
}
//第二种方式查找用户
user_t UserDaoImp::findUser(const QString& name)
{
    user_t user;
    DBHelper *helper = DBHelper::getIntance();
    helper->createConnect();
    QSqlQuery query;
    query.prepare("select username, passwd from tb_user where username=:username;");
    query.bindValue(":username",name);
    query.exec();
    while(query.next()){
        QString username = query.value(0).toString();
        QString userpasswd = query.value(1).toString();
        if(name == username){
            char* pname = username.toLocal8Bit().data();
            char* ppasswd = userpasswd.toLocal8Bit().data();
            strncpy(user.username, pname, 20);
            strncpy(user.userpasswd, ppasswd, 20);
            helper->destoryConnect();
            return user;
        }
    }
    helper->destoryConnect();
    qDebug()<<"user.uusername:"<<user.username<<"user.passwd:"<<user.userpasswd;
     strcpy(user.username, "");
    return user;
}

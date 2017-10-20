#include "ClientSocket.h"
#include "SocketManager.h"
#include <string.h>
#include <cstdlib>
#include <cstdio>
ClientSocket::ClientSocket(QTcpSocket* socket,QObject *parent)
    : QObject(parent),socket(socket)
{
    //当客户端有数据传输过来时，就触发信号
    QObject::connect(socket,SIGNAL(readyRead()),
                     this,SLOT(onReadyRead()));
}



//槽函数 读取套接字的数据 再将 发送给主界面
void ClientSocket::onReadyRead()
{

    Packet data;
    socket ->read((char*)&data,sizeof(data));
    qDebug()<<"clientSocket line 20:type"<<data.type<<","
           <<data.nickname<<","<<data.username;
    switch (data.type) {
    case TYPE_REG:
        regUser(&data);
        break;
    case TYPE_LOGIN:
        loginUser(&data);
        break;
    case TYPE_SELALL:
        selectAllUser(&data);
        break;
    default:
        break;
    }

}
void ClientSocket::regUser(Packet *data)
{
    QString nickname(data->nickname);
    QString passwd(data->passwd);
    QString phonenumber(data->phonenumber);
    User user(nickname,passwd,phonenumber);
    UserDao* ud = new UserDaoImp();
    QString username = ud->insertUser(user);//根据插入返回值 及用户名
    if(username.isEmpty())
    {
        //插入失败
        data->type = TYPE_REG_ERROR;
        strcpy(data->msg , "插入失败");
    }else if(username=="1")
    {
        //插入失败
        data->type = TYPE_REG_ERROR;
        strcpy(data->msg , "用户手机号存在");
    }
    else
    {
        strncpy(data->username,username.toStdString().data(),username.size());
        qDebug()<<"line 47:"<<data->username<<",username:"<<username;
        data->type = TYPE_REG_SUCCESS;

    }
    emit signalReturnInfo(socket,data,sizeof(Packet));
}

void ClientSocket::loginUser(Packet *data)
{
    qDebug()<<"59:"<<data->username;
    QString username(data->username);
    QString passwd(data->passwd);
    User user("",passwd,"",username);
    UserDao* ud = new UserDaoImp();
    vector<User> users = ud->selectUser(user);//根据插入返回值 及用户名
    vector<User>::iterator it;
    User usr;
    for(it=users.begin();it!=users.end();it++)
    {

        usr.setNickName( it->getNickname());
        usr.setPhonenumber(it->getPhonenumber());
        usr.setPasswd(it->getPasswd());
        usr.setUserName(it->getUsername());
    }
    QString errormsg = " ";
    if(users.size()>0)
    {
        errormsg = "密码错误";
        if(strcmp(usr.getPasswd().toStdString().data(),data->passwd)!=0)
        {
            strncpy(data->msg,errormsg.toStdString().data(),errormsg.size()+1);
            //登录失败
            data->type = TYPE_LOGIN_ERROR;
        }
        data->type = TYPE_LOGIN_SUCCESS;
    }
    else
    {
        errormsg= "用户不存在";
        strcpy(data->msg,errormsg.toStdString().data());
        //登录失败
        data->type = TYPE_LOGIN_ERROR;
    }
    qDebug()<<"94:data.msg:"<<data->msg;
    emit signalReturnInfo(socket,data,sizeof(Packet));
}
//查询全部
void ClientSocket::selectAllUser(Packet *data)
{
    UserDao* ud = new UserDaoImp();
    qDebug()<<"执行了查询所有";
    vector<User> users = ud->selectAllUser();//根据插入返回值 及用户名
    vector<User>::iterator it;
    qDebug()<<"users.size:"<<users.size();

    if(users.size()>=0)
    {
        int j = 0;
        for(it=users.begin();it!=users.end();it++)
        {
            j++;
            int id = it->getId();
            QString nickname = it->getNickname();
            QString username = it->getUsername();
            QString passwd = it->getPasswd();
            QString phonenumber = it->getPhonenumber();

            QString ret;
            ret += nickname;
            ret +=",";
            ret += username;
            ret +=",";
            ret +=passwd;
            ret += ",";
            ret += phonenumber;
            qDebug()<<"查询所有人131："<<ret;

#if 1
            strcpy(data->nickname,nickname.toStdString().data());
            strcpy(data->username,username.toStdString().data());
            strcpy(data->passwd,passwd.toStdString().data());
            strcpy(data->phonenumber,phonenumber.toStdString().data());
#endif
        }
        data->type = TYPE_SELALL_SUCCESS;


    }
    else
    {
        data->type = TYPE_SELALL_ERROR;
        QString errmsg = "查询失败";
        strcpy(data->msg,errmsg.toStdString().data()) ;

    }
    emit signalReturnInfo(socket,data,sizeof(Packet));
}

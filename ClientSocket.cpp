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
ClientSocket::~ClientSocket()
{
    UserDao *ud = new UserDaoImp();
    OnlineDao *od = new OnlineDaoImp();
    delete ud;
    delete od;
}

QTcpSocket* ClientSocket::getSocket ()const
{
    return socket;
}

//槽函数 读取套接字的数据 再将 发送给主界面
void ClientSocket::onReadyRead()
{
#if 0
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
    case TYPE_SEND_VER:
        sendVerification(&data);
        break;
    case TYPE_UPDATE:
        updateUser(&data);
        break;
    default:
        break;
    }
#endif
    //视频传输包
    user_t user;
    memset(&user, 0, sizeof(user));
    while(socket->read((char*)&user, sizeof(user))> 0){
        switch(user.type){
        case REG:
            server_reg(user);       //注册
            break;
        case LOGIN:
            server_login (user);    //登录
            break;
        case EXIT:
            server_exit(user);    //用户下线
            break;
        case ROOMNAME:
            server_roomName(user);  //聊天室列表
            break;
        case ROOMLIST:
            server_roomList(user);  //刷新聊天室
            break;
        case CHATNAME:
            server_chatName (user); //用户列表
            break;
        case CHATLIST:
            server_chatList (user); //刷新用户列表
            break;
        case QUIT:
            server_quit(user);      //退出聊天室
            break;
        case TEXT:
            server_chatText (user);  //文字聊天
            break;
        case VIDEO:
            server_chatText (user);     //视频聊天
            break;
        case UNVIDEO:
            server_chatText (user);     //关闭视频
            break;
        case BS:
            server_chatText (user);     //弹幕聊天
            break;
        default:break;
        }
    }

}
//第一种方式注册用户
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
//第一种方式登录用户
void ClientSocket::loginUser(Packet *data)
{
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
// 发送手机验证码
void ClientSocket::sendVerification(Packet *data)
{
    QString verification = utils.generateRandomNumber(4);
    if(verification.size()==4)
    {
        QString phonenumber(data->phonenumber);
        QString username(data->username);
        //User(QString nickname,QString passwd="1",QString phonenumber=0,QString username="",QString phoneverify="",int flag=0);
        User user("","",phonenumber,username,verification,0);
        UserDao* ud = new UserDaoImp();
        bool insertverify = ud->insertVerifi(user);//根据插入返回值 及用户名
        if(insertverify){
            data->type =  TYPE_SEND_VERSUCSS;
            strcpy(data->msg,verification.toStdString().data());
        }else
        {
            verification= "此手机号没有注册用户";
            strcpy(data->msg,verification.toStdString().data());
            data->type = TYPE_SEND_VERERROR;
        }

    }else
    {
        verification = "手机验证码错误";
        data->type =  TYPE_SEND_VERERROR;
        strcpy(data->msg,verification.toStdString().data());
    }
    emit signalReturnInfo(socket,data,sizeof(Packet));
}

void ClientSocket::updateUser(Packet *data)
{
    QString nickname(data->nickname);
    QString passwd(data->passwd);
    QString phonenumber(data->phonenumber);
    QString username(data->username);
    User user(nickname,passwd,phonenumber,username);
    UserDao* ud = new UserDaoImp();
    QString updateflag = ud->updateUser(user);//根据插入返回值 及用户名
    if(updateflag.contains("成功"))
    {
        data->type = TYPE_UPDATE_SUCCESS;
    }else
    {
        data->type = TYPE_UPDATE_ERROR;

    }
    strcpy(data->msg , updateflag.toStdString().data());
    emit signalReturnInfo(socket,data,sizeof(Packet));
}

//第二种方式

//注册
void ClientSocket::server_reg(user_t user)
{
    //    UserDao *ud = new UserDaoImp();
    //    QString pname = QString::fromLocal8Bit(user.username);
    //    mutex1.lock();
    //    user_t myuser = ud->findUser(pname);
    //    mutex1.unlock();
    //    if(myuser.username[0] != '\0'){
    //        strcpy(user.data, "用户名已存在");
    //    }
    //    else{
    //        mutex1.lock();
    //        if(ud->addUser(user)){
    //            strcpy(user.data, "注册成功");
    //        }
    //        else{
    //            strcpy(user.data, "注册失败");
    //        }
    //        mutex1.unlock();
    //    }
    emit this->sigWrite(socket, user, sizeof(user));
}

//登录
void ClientSocket::server_login(user_t user)
{
    UserDao *ud = new UserDaoImp();
    QString pname = QString::fromLocal8Bit(user.username);
    OnlineDao *od = new OnlineDaoImp();
    //mutex1.lock();
    user_t myuser = ud->findUser(pname);
    //mutex1.unlock();
    if(myuser.username[0] == '\0'){
        strcpy(user.data, "用户名不存在");
    }
    else{
        if(strcmp(myuser.userpasswd, user.userpasswd) == 0){
            // mutex2.lock();
            char *ptr = od->findOnline(pname);
            // mutex2.unlock();
            qDebug()<<"pname:"<<pname;
            if(ptr != NULL){
                strcpy(user.data, "该用户已在线");
            }
            else{
                //mutex2.lock();
                od->addOnline(pname);
                //mutex2.unlock();
                strcpy(user.data, "登陆成功");
                user.flag = UP;
            }
        }
        else{
            strcpy(user.data, "密码错误");
        }
    }
    qDebug()<<"登录："<<user.data;
    emit this->sigWrite(socket, user, sizeof(user));
}

//用户下线
void ClientSocket::server_exit(user_t user)
{
    OnlineDao *od = new OnlineDaoImp();
    QString pname = QString::fromLocal8Bit(user.username);
    QString proom = QString::fromLocal8Bit(user.roomName);
    // mutex2.lock();
    od->delOnline(pname);
    // mutex2.unlock();
    if(user.flag == MASTER){    //当房主退出客户端时，通知房间里的其他人离开房间
        ChatManager *cm = ChatManager::getInstance();
        vector<ChatRoom> rooms = cm->getAllChat();
        vector<ChatRoom>::iterator it;
        for(it = rooms.begin(); it != rooms.end(); it++){
            ChatRoom mychat = *it;
            if(mychat.getRoomName() == proom){
                QTcpSocket *every_socket = mychat.getSocket();
                emit this->sigWrite (every_socket, user, sizeof(user_t));
            }
        }
    }
}

//刚进入二级菜单时将用户名作为聊天室名发送给所有在线用户
void ClientSocket::server_roomName (user_t user)
{
    SocketManager *sockets = SocketManager::getIntance();
    vector<ClientSocket*> clients = sockets->getAllSocket ();
    vector<ClientSocket*>::iterator it;
    int i =0;
    for(it = clients.begin (); it != clients.end (); it++){
        i++;
        ClientSocket *client = *it;
        QTcpSocket *every_socket = client->getSocket ();
        emit this->sigWrite (every_socket, user, sizeof(user_t));
    }
        qDebug()<<"查看房间列表循环结束："<<i;
}

//刚进入聊天室时将用户名添加到所有聊天室内成员的聊天室列表
void ClientSocket::server_chatName (user_t user)
{
    qDebug()<<"chatName:user.name:"<<user.username<<"user.roomName:"<<user.roomName;
    QString username = QString::fromLocal8Bit (user.username);
    QString roomName = QString::fromLocal8Bit (user.roomName);
    ChatRoom chat(username, roomName, user.flag, socket);
    ChatManager *cm = ChatManager::getInstance ();
    cm->insertChat (chat);
    vector<ChatRoom> rooms = cm->getAllChat ();
    vector<ChatRoom>::iterator it;
    for(it = rooms.begin (); it != rooms.end (); ++it){
        ChatRoom mychat = *it;
        if(mychat.getRoomName () == roomName){
            QTcpSocket* every_socket = mychat.getSocket ();
            emit this->sigWrite (every_socket, user, sizeof(user_t));
        }
    }
}

//实现文字聊天
void ClientSocket::server_chatText (user_t user)
{
    QString roomName = QString::fromLocal8Bit (user.roomName);
    ChatManager *cm = ChatManager::getInstance ();
    vector<ChatRoom> rooms = cm->getAllChat ();
    vector<ChatRoom>::iterator it;
    for(it = rooms.begin (); it != rooms.end (); ++it){
        ChatRoom chat = *it;
        if(chat.getRoomName () == roomName){
            user.flag = chat.getFlag ();
            QTcpSocket *every_socket = chat.getSocket ();
            emit this->sigWrite (every_socket, user, sizeof(user_t));
        }
    }
}


//刷新聊天室列表
void ClientSocket::server_roomList(user_t user)
{
    OnlineDao *od = new OnlineDaoImp();
    vector<QString> v_name = od->selectOnline ();
    vector<QString>::iterator it;
    for(it = v_name.begin (); it != v_name.end (); ++it){
        QString q_name = *it;
        QByteArray ba_name = q_name.toLocal8Bit ();
        char* c_name = ba_name.data ();
        strncpy(user.roomName, c_name, 20);
        emit this->sigWrite (socket, user, sizeof(user_t));
    }
}

//刷新聊天室用户列表
void ClientSocket::server_chatList(user_t user)
{
    QString roomName = QString::fromLocal8Bit (user.roomName);
    ChatManager *cm = ChatManager::getInstance ();
    vector<ChatRoom> rooms = cm->getAllChat ();
    vector<ChatRoom>::iterator it;
    for(it = rooms.begin (); it != rooms.end (); ++it){
        ChatRoom chat = *it;
        if(chat.getRoomName () == roomName){
            QString qname = chat.getUserName ();
            QByteArray ba_name = qname.toLocal8Bit ();
            char *c_name = ba_name.data ();
            strncpy(user.chatname, c_name, 20);
            user.flag = chat.getFlag ();
            emit this->sigWrite (socket, user, sizeof(user_t));
        }
    }
}

//退出聊天室处理
void ClientSocket::server_quit(user_t user)
{
    QString name = QString::fromLocal8Bit (user.username);
    ChatManager *cm = ChatManager::getInstance ();
    cm->eraseChat (name);
}

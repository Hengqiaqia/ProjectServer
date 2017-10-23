#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include "packet.h"
#include "UserDaoImp.h"
#include "Utils.h"
#include "ChatManager.h"
#include<QMutex>
#include "userpacket.h"
#include "OnlineDaoImp.h"


class ClientSocket : public QObject
{
    Q_OBJECT
public:
    explicit ClientSocket(QTcpSocket * socket,QObject *parent = nullptr);
    ~ClientSocket();
    void regUser(Packet* data);//注册
    void loginUser(Packet* data);//登录
    void selectAllUser(Packet* data);//查询全部
    void sendVerification(Packet* data);//修改密码发送手机验证码
    void updateUser(Packet* data);//更新用户信息

    void server_reg(user_t user);
    void server_login(user_t user);
    void server_exit(user_t user);
    void server_roomName(user_t user);
    void server_chatName(user_t user);
    void server_roomList(user_t user);
    void server_chatList(user_t user);
    void server_chatText(user_t user);
    void server_quit(user_t user);

    QTcpSocket* getSocket()const;


private:
    QTcpSocket* socket;
    Utils utils;
    static QMutex mutex1;
    static QMutex mutex2;

signals:
    //视频
    void sigWrite(QTcpSocket *socket, user_t user, int len);

    //单对单
    void signalReturnInfo(QTcpSocket* socket,Packet* str,int len);
public slots:
    void onReadyRead();
};

#endif // CLIENTSOCKET_H

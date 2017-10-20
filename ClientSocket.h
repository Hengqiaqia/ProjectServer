#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include "packet.h"
#include "UserDaoImp.h"
class ClientSocket : public QObject
{
    Q_OBJECT
public:
    explicit ClientSocket(QTcpSocket * socket,QObject *parent = nullptr);
    void regUser(Packet* data);//注册
    void loginUser(Packet* data);//登录
    void selectAllUser(Packet* data);//查询全部

private:
    QTcpSocket* socket;

signals:
    //单对单
     void signalReturnInfo(QTcpSocket* socket,Packet* str,int len);
public slots:
       void onReadyRead();
};

#endif // CLIENTSOCKET_H

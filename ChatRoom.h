#ifndef CHATROOM_H
#define CHATROOM_H

#include<QString>
#include<QTcpSocket>

class ChatRoom
{
public:
    ChatRoom(const QString& username, const QString& roomName, int flag, QTcpSocket* socket);
    ChatRoom();
    QString getUserName()const;
    QString getRoomName()const;
    int getFlag()const;
    QTcpSocket* getSocket()const;
private:
    QString username;
    QString roomName;
    int flag;
    QTcpSocket *socket;

};

#endif // CHATROOM_H

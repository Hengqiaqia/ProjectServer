#include "ChatRoom.h"

ChatRoom::ChatRoom(const QString& username, const QString& roomName, int flag, QTcpSocket* socket)
    :username(username), roomName(roomName),flag(flag), socket(socket)
{


}

ChatRoom::ChatRoom()
{

}

QString ChatRoom::getUserName()const
{
    return username;
}

QString ChatRoom::getRoomName()const
{
    return roomName;
}

int ChatRoom::getFlag ()const
{
    return flag;
}

QTcpSocket* ChatRoom::getSocket ()const
{
    return socket;
}

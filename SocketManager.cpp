#include "SocketManager.h"

SocketManager* SocketManager::intance = 0;
SocketManager::SocketManager(QObject *parent) : QObject(parent)
{

}

SocketManager *SocketManager::getIntance()
{
    if(0==intance)
    {
        intance = new SocketManager();
    }
    return intance;
}

void SocketManager::addSocket(QTcpSocket *socket)
{
    sockets.push_back(socket);
}

void SocketManager::sendDataToAll(const char* str,int len)
{
    vector<QTcpSocket*>::iterator it;
    for(it=sockets.begin();it!=sockets.end();it++)
    {
        QTcpSocket* socket = *it;
        emit sigWrite(socket,str,len);
    }
}

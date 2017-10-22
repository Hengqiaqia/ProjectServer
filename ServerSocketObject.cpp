#include "ServerSocketObject.h"

#include <QBuffer>
#include <QDebug>

ServerSocketObject::ServerSocketObject(QObject *parent, int consumer_socket):
    QObject(parent)
{
    _size = 0;
    workSocket = new ServerSocket(this,consumer_socket);
    connect(workSocket,SIGNAL(open_dev(QString,int)),this,SIGNAL(send_dev_name(QString,int)));
    connect(workSocket,SIGNAL(disconnected(int)),this,SIGNAL(free_WriteThread(int)));
    connect(workSocket,SIGNAL(dealWithCMD_signals(int,QString,int)),
            this,SIGNAL(serverDealWithCMD_signals(int,QString,int)));
}

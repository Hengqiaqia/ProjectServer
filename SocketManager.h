#ifndef SOCKETMANAGER_H
#define SOCKETMANAGER_H

#include <QObject>
#include <QTcpSocket>
#include <vector>
using namespace std;
class SocketManager : public QObject
{
    Q_OBJECT
private:
    vector<QTcpSocket*> sockets;
    static SocketManager* intance;
public:
    explicit SocketManager(QObject *parent = nullptr);
    static SocketManager* getIntance();
    void addSocket(QTcpSocket* socket);
    void sendDataToAll(const char* str,int len);
signals:
    void sigWrite(QTcpSocket* socket,const char* str,int len);
public slots:
};

#endif // SOCKETMANAGER_H

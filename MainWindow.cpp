#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QHostAddress>
#include <QTcpSocket>
#include "ClientSocket.h"
#include <QThread>
#include "SocketManager.h"
#include <QDebug>
#include "UserDaoImp.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server= new QTcpServer(this);
    QObject::connect(server,SIGNAL(newConnection()),
                     this,SLOT(onNewConnection()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{

    qDebug()<<"点击了关闭x按钮";
}

void MainWindow::on_btn_listen_clicked()
{

    if(server->isListening())
    {
        ui->te_show->append("已经监听~~");
        return;
    }
    bool islitensuccess = server->listen(QHostAddress::Any,8888);
    if(islitensuccess)
    {
        ui->te_show->append("监听成功~");
    }else
    {
        ui->te_show->append("监听失败~");
    }
}

void MainWindow::onNewConnection()
{

    ui->te_show->append("someconnected connected");

    SocketManager* sm = SocketManager::getIntance();
    QTcpSocket* client=server->nextPendingConnection();
    // 在主界面上显示客户端连接的ip
    QHostAddress ip = client->peerAddress();
    int port = client->peerPort();
    QString info ="IP:"+ ip.toString()+"端口："+QString::number(port);
    qDebug()<<"server69line 连接："<<info;
    ui->te_show->append(info);
   // sm->addSocket(client)

    //cs 专门管理单个客户端的类
    ClientSocket* cs = new ClientSocket(client);

    sm->insertSocket (cs);

    // 创建线程专门处理某个客户端
    QThread *thread = new QThread(this);

    connect(cs,SIGNAL(signalReturnInfo(QTcpSocket*,Packet*,int)),
            this,SLOT(onSignalReturnInfo(QTcpSocket*,Packet*,int)));

    QObject::connect(client,SIGNAL(disconnected()),
                     cs,SLOT(deleteLater()));

    QObject::connect(client,SIGNAL(disconnected()),
                     thread,SLOT(quit()));

    QObject::connect(client,SIGNAL(disconnected()),
                     this,SLOT(onClienQuit()));
    qRegisterMetaType<user_t>("user_t");    //完成结构体注册
    connect(cs, SIGNAL(sigWrite(QTcpSocket*,user_t,int)),
                     this, SLOT(onSigWrite(QTcpSocket*,user_t,int)));
    cs->moveToThread(thread);
    thread->start();


}

void MainWindow::onClienQuit()
{
    qDebug()<<"client quit";
}
//登录 注册 第一种方式
void MainWindow::onSignalReturnInfo(QTcpSocket *client, Packet *data, int size)
{
    qDebug()<<"data.username:"<<data->username;
    client->write((char*)data,size);
}
//第二种方式
void MainWindow::onSigWrite(QTcpSocket *socket, user_t user, int len)
{
    socket->write((char *)&user, len);
}


void MainWindow::on_btn_usermanger_clicked()
{
    userlist = new UserList();
    userlist->show();
}

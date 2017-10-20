#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include "packet.h"
#include "UserList.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void closeEvent(QCloseEvent *event);
private slots:
    void on_btn_listen_clicked();
    void onNewConnection();

    //客户端退出 自定义槽函数
    void onClienQuit();
    //接收客户端信息 发送回去
    void onSignalReturnInfo(QTcpSocket*,Packet*,int);

    void on_btn_usermanger_clicked();

private:
    Ui::MainWindow *ui;
    QTcpServer *server;

    UserList* userlist;

};

#endif // MAINWINDOW_H

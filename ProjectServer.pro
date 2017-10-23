#-------------------------------------------------
#
# Project created by QtCreator 2017-10-18T12:49:10
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProjectServer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0



SOURCES += \
        main.cpp \
        MainWindow.cpp \
    ClientSocket.cpp \
    SocketManager.cpp \
    DBHelper.cpp \
    User.cpp \
    UserDao.cpp \
    UserDaoImp.cpp \
    Utils.cpp \
    UserList.cpp \
    UserDialog.cpp \
    ServerSocket.cpp \
    ChatRoom.cpp \
    ChatManager.cpp \
    OnlineDao.cpp \
    OnlineDaoImp.cpp

HEADERS += \
        MainWindow.h \
    ClientSocket.h \
    SocketManager.h \
    DBHelper.h \
    User.h \
    UserDao.h \
    UserDaoImp.h \
    Utils.h \
    packet.h \
    UserList.h \
    UserDialog.h \
    CommandType.h \
    LogInfo.h \
    Permission.h \
    ServerSocket.h \
    ChatRoom.h \
    ChatManager.h \
    userpacket.h \
    OnlineDao.h \
    OnlineDaoImp.h


FORMS += \
        MainWindow.ui \
    UserList.ui \
    UserDialog.ui \
    ShowLog.ui \
    servermainwindow.ui

RESOURCES += \
    res.qrc


#ifndef USER_H
#define USER_H

#include <QString>
#include <QDebug>
class User
{
public:
    User();
    //用户名是系统分配的， 可以不传
    User(QString nickname,QString passwd="1",QString phonenumber=0,QString username="",QString phoneverify="",int flag=0);
    int getId()const;
    QString getNickname()const;
    QString getPasswd()const;
    QString getPhonenumber()const;
    QString getUsername()const;
    void setId(const int id);
    void setNickName(const QString nickname);
    void setPasswd(const QString passwd);
    void setPhonenumber(const QString phonenumber);
    void setUserName(const QString username);
    void setPhoneVerify(const QString phoneverify);
    QString getPhoneVerify()const;
    void setSendFlag(const int sendflag);
    int getSendFlag()const;
    void printlf()const;
private:
    int id ;
    QString username ;
    QString nickname ;
    QString  passwd  ;
    QString  phonenumber ;
    QString phoneverify;//验证码
    int sendflag;
};

#endif // USER_H

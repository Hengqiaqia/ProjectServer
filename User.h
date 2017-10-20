#ifndef USER_H
#define USER_H

#include <QString>
class User
{
public:
    User();
    //用户名是系统分配的， 可以不传
    User(QString nickname,QString passwd="1",QString phonenumber=0,QString username="");
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
private:
    int id ;
    QString username ;
    QString nickname ;
    QString  passwd  ;
    QString  phonenumber ;
};

#endif // USER_H

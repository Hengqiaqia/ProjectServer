#include "User.h"

User::User()
{

}

User::User(QString nickname, QString passwd, QString phonenumber, QString username, QString phoneverify, int sendflag)
    :nickname(nickname),passwd(passwd),phonenumber(phonenumber),username(username),phoneverify(phoneverify),sendflag(sendflag)
{

}

int User::getId() const
{
    return id;
}

QString User::getNickname() const
{
    return nickname;
}

QString User::getPasswd() const
{
    return passwd;
}

QString User::getPhonenumber() const
{
    return phonenumber;
}

QString User::getUsername() const
{
    return username;
}

void User::setId(const int id)
{
    this->id = id;
}

void User::setNickName(const QString nickname)
{
    this->nickname = nickname;
}

void User::setPasswd(const QString passwd)
{
    this->passwd = passwd;
}

void User::setPhonenumber(const QString phonenumber)
{
    this->phonenumber = phonenumber;
}

void User::setUserName(const QString username)
{
    this->username = username;
}


void User::setPhoneVerify(const QString phoneverify)
{
    this->phoneverify = phoneverify;
}

QString User::getPhoneVerify()const
{
    return phoneverify;
}

void User::setSendFlag(const int sendflag)
{
    this->sendflag = sendflag;
}

int User::getSendFlag()const
{
    return sendflag;
}

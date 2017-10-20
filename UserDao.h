#ifndef USERDAO_H
#define USERDAO_H
#include "User.h"
#include <vector>
using namespace std;
class UserDao
{
public:
    virtual QString insertUser(const User& user)=0;
    virtual vector<User> selectAllUser()=0;
    virtual bool deleteSUser(const User& user)=0;
    virtual bool updateUser(const User& user)=0;
    virtual vector<User> selectUser(const User& user)=0;//查询单个
    virtual bool updateUserInfo(const User &user)=0;

    UserDao();
    virtual ~UserDao();

};

#endif // USERDAO_H

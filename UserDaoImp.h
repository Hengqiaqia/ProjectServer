#ifndef USERDAOIMP_H
#define USERDAOIMP_H
#include "UserDao.h"
#include "Utils.h"
class UserDaoImp : public UserDao
{
public:
    UserDaoImp();
    QString insertUser(const User& user) ;
    vector<User> selectAllUser() ;
    bool deleteSUser(const User& user) ;
    bool updateUser(const User& user) ;
    vector< User > selectUser(const User& user) ;//查询单个
    bool updateUserInfo(const User &user);

    bool insertVerifi(const User& ver);//增加验证码
    bool updateVerifi(const User& ver);//修改验证码
private:
     Utils utils;

};

#endif // USERDAOIMP_H

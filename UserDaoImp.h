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
};

#endif // USERDAOIMP_H

#ifndef ONLINEDAOIMP_H
#define ONLINEDAOIMP_H

#include "OnlineDao.h"
#include "DBHelper.h"
#include "userpacket.h"
class OnlineDaoImp : public OnlineDao
{
public:
    OnlineDaoImp();
    bool addOnline(QString& name);
    char* findOnline(QString& name);
    bool delOnline(QString& name);
    vector<QString> selectOnline();
private:
    vector<QString> onlines;
};
#endif // ONLINEDAOIMP_H

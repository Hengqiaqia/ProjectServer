#ifndef ONLINEDAO_H
#define ONLINEDAO_H
#include <QString>
#include <vector>
using namespace std;

class OnlineDao
{
public:
    OnlineDao();
    virtual ~OnlineDao();
    virtual bool addOnline(QString& name) = 0;
    virtual char* findOnline(QString& name) = 0;
    virtual bool delOnline(QString& name) = 0;
    virtual vector<QString> selectOnline() = 0;
};

#endif // ONLINEDAO_H

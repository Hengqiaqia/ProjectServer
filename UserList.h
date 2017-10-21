#ifndef USERLIST_H
#define USERLIST_H

#include <QWidget>
#include "UserDaoImp.h"
#include "User.h"
#include "UserDao.h"
#include "DBHelper.h"
#include <QSqlQueryModel>
#include "UserDialog.h"
#include <QMessageBox>
namespace Ui {
class UserList;
}

class UserList : public QWidget
{
    Q_OBJECT

public:
    explicit UserList(QWidget *parent = 0);
    ~UserList();
    void showMsg();
private slots:
    void on_btn_all_clicked();

    void on_btn_add_clicked();

    void on_btn_update_clicked();

    void on_btn_del_clicked();

    void on_btn_search_clicked();

    void onSignalinsert(User);
    void onSignaldel(User);
    void onSignalupdata(User);
    void onSignalselect(User);
    void onSignalupdatever(User);
    void on_btn_verify_clicked();

private:
    Ui::UserList *ui;
    QSqlQueryModel* model;
    UserDialog* userdialog;
};

#endif // USERLIST_H

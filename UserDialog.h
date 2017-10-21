#ifndef USERDIALOG_H
#define USERDIALOG_H

#include <QWidget>
#include "User.h"
#include <QMessageBox>
namespace Ui {
class UserDialog;
}

class UserDialog : public QWidget
{
    Q_OBJECT

public:
    explicit UserDialog(int flag,QString title,QWidget *parent = 0);
    ~UserDialog();
signals:
    void signalinsert(User);
    void signaldel(User);
    void signalupdata(User);
    void signalselect(User);
    void signalupdatever(User);
private slots:
    void on_btn_cancel_clicked();

    void on_btn_ok_clicked();

private:
    Ui::UserDialog *ui;
    int flag;
    QString title;
};

#endif // USERDIALOG_H

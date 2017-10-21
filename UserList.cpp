#include "UserList.h"
#include "ui_UserList.h"

UserList::UserList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserList)
{
    ui->setupUi(this);
    model = new QSqlQueryModel();
    ui->te_show->hide();

}

UserList::~UserList()
{
    delete ui;
}

void UserList::showMsg()
{
    ui->te_show->hide();
    ui->tableView->show();
    DBHelper* helper = DBHelper::getIntance();
    helper->createConnect();
    model->setQuery("select * from tb_user;");
    ui->tableView->setModel(model);
    helper->destoryConnect();


}
//查询所有
void UserList::on_btn_all_clicked()
{
    showMsg();
}
//add
void UserList::on_btn_add_clicked()
{
    userdialog =  new UserDialog(1,"增加用户");
    connect(userdialog,SIGNAL(signalinsert(User)),this,SLOT(onSignalinsert(User)));
    userdialog->show();
}
//修改用户
void UserList::on_btn_update_clicked()
{
    userdialog =  new UserDialog(2,"更新用户");
    connect(userdialog,SIGNAL(signalupdata(User)),this,SLOT(onSignalupdata(User)));
    userdialog->show();
}
//删除用户
void UserList::on_btn_del_clicked()
{
    userdialog =  new UserDialog(3,"删除用户");
    connect(userdialog,SIGNAL(signaldel(User)),this,SLOT(onSignaldel(User)));
    userdialog->show();
}
//查询用户
void UserList::on_btn_search_clicked()
{
    userdialog =  new UserDialog(4,"查询用户");
    connect(userdialog,SIGNAL(signalselect(User)),this,SLOT(onSignalselect(User)));
    userdialog->show();
}

void UserList::onSignalinsert(User user)
{
    UserDao* ud = new UserDaoImp();
    QString flagname = ud->insertUser(user);
    QString result = "";
    qDebug()<<"flagname:"<<flagname;
    if(!flagname.isEmpty()&&flagname!="1")
    {
        result="增加用户成功";
    }else if(flagname=="1")
    {
        result = "用户手机号已存在";
    }
    else
    {
        result="增加用户失败";
    }
    QMessageBox::information(this,"服务端增加",result);
    showMsg();
}

void UserList::onSignaldel(User user)
{
    UserDao* ud = new UserDaoImp();
    bool delflag = ud->deleteSUser(user);
    QString result = "";
    if(delflag)
    {
        result="删除用户成功";
    }else
    {
        result="删除用户失败";
    }
    QMessageBox::information(this,"服务端删除",result);
    showMsg();
}

void UserList::onSignalupdata(User user)
{
    UserDao* ud = new UserDaoImp();
    QString result = ud->updateUser(user);
//    if(result)
//    {
//        result="更新用户成功";
//    }else
//    {
//        result="更新用户失败";
//    }
    QMessageBox::information(this,"服务端更新",result);
    showMsg();
}

void UserList::onSignalselect(User user)
{
    ui->tableView->hide();
    ui->te_show->show();
    UserDao* ud = new UserDaoImp();
    vector<User> users = ud->selectUser(user);//根据插入返回值 及用户名
    vector<User>::iterator it;
    User usr;
    for(it=users.begin();it!=users.end();it++)
    {

        QString nickname = it->getNickname() ;
        QString phonenumber=it->getPhonenumber();
        QString passwd=it->getPasswd();
        QString username=it->getUsername();
        QString ret="nickname=";
        ret += nickname;
        ret += "----phonenumber=";
        ret += phonenumber;
        ret += "----passwd=";
        ret += passwd;
        ret += "----username=";
        ret += username;
        ui->te_show->append(ret);
    }
}

void UserList::onSignalupdatever(User user)
{
    UserDao* ud = new UserDaoImp();
    bool uodateflag = ud->updateVerifi(user);
    QString result = "";
    if(uodateflag)
    {
        result="修改验证码成功";
    }else
    {
        result="修改验证码失败";
    }
    QMessageBox::information(this,"服务端更新",result);
    showMsg();
}
//修改验证码
void UserList::on_btn_verify_clicked()
{
    userdialog =  new UserDialog(5,"修改验证码");
    connect(userdialog,SIGNAL(signalupdatever(User)),this,SLOT(onSignalupdatever(User)));
    userdialog->show();
}


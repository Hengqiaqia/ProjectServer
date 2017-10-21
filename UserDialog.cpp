#include "UserDialog.h"
#include "ui_UserDialog.h"

UserDialog::UserDialog(int flag,QString title,QWidget *parent) :
    flag(flag),title(title),QWidget(parent),
    ui(new Ui::UserDialog)
{
    ui->setupUi(this);
    QWidget::setWindowTitle(title);

    if(flag == 1)
    {
        //增加用户
        ui->le_username->setPlaceholderText("账号系统自动生成");
        ui->le_username->setEnabled(false);
        ui->le_username->setFocusPolicy(Qt::NoFocus);//失去焦点
        ui->le_passwd->setPlaceholderText("请输入密码");
        ui->le_passwd->setEchoMode(QLineEdit::Password);
        ui->le_phonenumber->setPlaceholderText("请输入手机号码");
        /**
         * 验证手机号码
         *
         * 移动号码段:139、138、137、136、135、134、150、151、152、157、158、159、182、183、187、188、147
         * 联通号码段:130、131、132、136、185、186、145
         * 电信号码段:133、153、180、189
         *
         **/
        QRegExp regxnumber("^((13[0-9])|(14[5|7])|(15([0-3]|[5-9]))|(18[0,5-9]))\\d{8}$");
        QValidator *validator = new QRegExpValidator(regxnumber ,  ui->le_phonenumber );
        ui->le_phonenumber->setValidator( validator );

        ui->le_phonenumber->setMaxLength(11);
        ui->le_nickname->setPlaceholderText("请输入昵称");
        ui->label_verify->hide();
        ui->le_phoneverifiy->hide();
    }
    else if(flag == 2)
    {
        //更新用户
        ui->le_username->setPlaceholderText("请输入账号");
        ui->le_passwd->setPlaceholderText("请输入密码");
        ui->le_passwd->setEchoMode(QLineEdit::Password);
        ui->le_phonenumber->setPlaceholderText("请输入手机号码");
        QRegExp regx("[0-9]+$");
        QValidator *validator = new QRegExpValidator(regx,  ui->le_phonenumber );
        ui->le_phonenumber->setValidator( validator );
        ui->le_phonenumber->setMaxLength(11);
        ui->le_nickname->setPlaceholderText("请输入昵称");
        ui->label_verify->hide();
        ui->le_phoneverifiy->hide();
    }
    else if(flag == 3)
    {
        //删除用户
        ui->le_username->setPlaceholderText("请输入账号");
        ui->le_passwd->setPlaceholderText("请输入密码");
        ui->le_passwd->setEchoMode(QLineEdit::Password);
        ui->le_phonenumber->setPlaceholderText("请输入手机号码");
        QRegExp regx("[0-9]+$");
        QValidator *validator = new QRegExpValidator(regx,  ui->le_phonenumber );
        ui->le_phonenumber->setValidator( validator );
        ui->le_phonenumber->setMaxLength(11);
        ui->le_nickname->setPlaceholderText("请输入昵称");
        ui->label_verify->hide();
        ui->label_passwd->hide();
        ui->le_passwd->hide();

        ui->le_phoneverifiy->hide();
    }
    else if(flag == 4)
    {
        // 查询用户
        ui->le_username->setPlaceholderText("请输入账号");
        ui->le_phonenumber->setPlaceholderText("请输入手机号码");
        QRegExp regx("[0-9]+$");
        QValidator *validator = new QRegExpValidator(regx,  ui->le_phonenumber );
        ui->le_phonenumber->setValidator( validator );
        ui->le_phonenumber->setMaxLength(11);
        ui->le_nickname->setPlaceholderText("请输入昵称");
        ui->label_verify->hide();
        ui->label_passwd->hide();
        ui->le_passwd->hide();
        ui->label_nickname->hide();
        ui->le_nickname->hide();
        ui->le_phoneverifiy->hide();
    }
    else if(flag == 5)
    {
        // 修改验证码
        ui->le_username->setPlaceholderText("请输入账号");
        ui->le_phonenumber->setPlaceholderText("请输入手机号码");
        QRegExp regx("[0-9]+$");
        ui->label_passwd->hide();
        ui->le_passwd->hide();
        ui->label_nickname->hide();
        ui->le_nickname->hide();
        QValidator *validator = new QRegExpValidator(regx,  ui->le_phonenumber );
        ui->le_phonenumber->setValidator( validator );
        ui->le_phonenumber->setMaxLength(11);
        ui->le_phoneverifiy->setPlaceholderText("请输入验证码");
    }
}

UserDialog::~UserDialog()
{
    delete ui;
}

void UserDialog::on_btn_cancel_clicked()
{
    this->close();
}

void UserDialog::on_btn_ok_clicked()
{
    QString  username = ui->le_username->text();
    QString passwd = ui->le_passwd->text();
    QString phonenumber = ui->le_phonenumber->text();
    QString nickname = ui->le_nickname->text();
    QString verify=ui->le_phoneverifiy->text();
    User user( nickname, passwd, phonenumber, username,verify,0);
    if(flag == 1)
    {
        if(!phonenumber.isEmpty()&&!nickname.isEmpty()){
            emit signalinsert(user);
        }else{
            QMessageBox::critical(this,"增加用户","请输入昵称，手机号");
        }
    }
    else if(flag == 2)
    {
        if(!username.isEmpty()&&!phonenumber.isEmpty()){
            emit signalupdata(user);
        }else{
            QMessageBox::critical(this,"修改用户","请输入账号，手机号");
        }
    }
    else if(flag == 3)
    {
        if(!username.isEmpty()&&!phonenumber.isEmpty()){
            emit signaldel(user);
        }else{
            QMessageBox::critical(this,"删除用户","请输入账号，手机号");
        }

    }
    else if(flag == 4)
    {
        emit signalselect(user);
    }
    else if(flag == 5)
    {
        if(!verify.isEmpty()&&!username.isEmpty()&&!phonenumber.isEmpty()){
            emit signalupdatever(user);
        }else{
            QMessageBox::critical(this,"修改验证码","请输入账号，手机号，验证码");
        }
    }
    this->close();
}

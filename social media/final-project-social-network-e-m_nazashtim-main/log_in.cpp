#include "log_in.h"
#include "ui_log_in.h"
#include"fileoperations.h"
#include"userpage.h"
#include"QMessageBox"
#include<fstream>

using namespace std;
log_in::log_in(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::log_in)
{
    ui->setupUi(this);
}

log_in::~log_in()
{
    delete ui;
}

void log_in::on_pushButton_2_clicked()
{
    fileoperations *fop=new fileoperations;

    QString user=ui->usertxt->text();
    QString pass=ui->passtxt->text();

       if(fop->search(user,pass)) //save user info in another file
       {
           map<string,string>info;
          info=fop->read_userandemail_from_file();

          ofstream userprofile("userprofile.txt",ios::trunc);
          userprofile<<user.toStdString()<<" "<<pass.toStdString()<<" "<<info[user.toStdString()];

          userprofile.close();
          userpage *up=new userpage();

           up->show();
           hide();
       }
       else
       {
           ui->alarmtxt->setText("No user with this information found!");
       }
}

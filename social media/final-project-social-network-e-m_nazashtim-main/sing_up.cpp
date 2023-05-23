#include "sing_up.h"
#include "ui_sing_up.h"
#include "fileoperations.h"
#include<QMessageBox>
#include"mainwindow.h"
using namespace std;
sing_up::sing_up(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sing_up)
{
    ui->setupUi(this);
}

sing_up::~sing_up()
{

   delete ui;

}

void sing_up::on_pushButton_clicked()
{
    fileoperations fop;
    MainWindow *m=new MainWindow;

    QString username=ui->usertxt->text();
    QString password=ui->passtxt->text();
    QString email=ui->emailtxt->text();


   if(fop.isUnique(username,password))
   {
       fop.write_to_file(username,password,email);
       hide();
       m->show();
   }
   else
   {
       ui->alarmtxt->setText("Username must be unique!");
   }

}

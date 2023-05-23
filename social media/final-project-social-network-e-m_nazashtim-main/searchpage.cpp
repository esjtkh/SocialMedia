#include "searchpage.h"
#include "ui_searchpage.h"
#include<fstream>
#include<map>
#include<fileoperations.h>

using namespace std;
searchpage::searchpage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::searchpage)
{
    map<string,string>mp;
    fileoperations fop;
    ifstream file("searchuser.txt");
    string searcheduser,email;

    file>>searcheduser;

    mp=fop.read_userandemail_from_file();

    email=mp[searcheduser];

    ui->setupUi(this);

    ui->usertxt->setText(QString::fromStdString(searcheduser));
    ui->emailtxt->setText(QString::fromStdString(email));
}

searchpage::~searchpage()
{
    delete ui;
}

void searchpage::on_followbtn_clicked()
{
   string following=ui->usertxt->text().toStdString();
   fileoperations fop;
   ifstream file("userprofile.txt");
   string follower;

   file>>follower;
   file.close();

   if(fop.check_searcheduser(following,follower))
   {
       fop.addfollowingandfollower(following,follower);
       this->close();
   }
   else
   {
       ui->usertxt->setText("You have followed this user before");
   }


}

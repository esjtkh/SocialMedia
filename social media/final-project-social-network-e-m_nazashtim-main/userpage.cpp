#include "userpage.h"
#include "ui_userpage.h"
#include "userprofile.h"
#include"fileoperations.h"
#include"searchpage.h"
#include <fstream>
#include <map>
#include<QString>
#include<followerpage.h>
#include"mainwindow.h"
#include <suggestion.h>

using namespace std;
userpage::userpage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::userpage)
{
    multimap<string,string>mp;
    fileoperations *fop=new fileoperations;
    ifstream file("userprofile.txt");
    string user;

    ui->setupUi(this);

    file>>user;

////////////////////////////// showing followers and followings ///////////////////////////////////////

    mp=fop->read_followers(); //use multimap to prevent search from being O(n)

    //time complexity O(log n)
    auto itr1=mp.lower_bound(user);
    auto itr2=mp.upper_bound(user);

    while(itr1!=itr2)
    {
        if(itr1->first==user)
        {
            QString a=QString::fromStdString(itr1->second);
            ui->list_followers->addItem(a);
        }
        itr1++;
    }

    mp=fop->read_followings();
    itr1=mp.lower_bound(user);
    itr2=mp.upper_bound(user);

    while(itr1!=itr2)
    {
        if(itr1->first==user)
        {
            QString a=QString::fromStdString(itr1->second);
            ui->list_following->addItem(a);
        }
        itr1++;
    }
//////////////////////////// showing messages /////////////////////////////////////////////////////////////

    mp=fop->read_messages();
    QString tmp="";

    itr1=mp.lower_bound(user);
    itr2=mp.upper_bound(user);

    while(itr1!=itr2)
    {
        if(itr1->first==user)//when there is no user with given username
        {
            QString a=QString::fromStdString(itr1->second);

            ui->history->append(a);
        }
        itr1++;
    }
}

userpage::~userpage()
{
    delete ui;
}

void userpage::on_pushButton_2_clicked()
{
    userprofile*u=new userprofile;
    u->show();
    this->hide();
}

void userpage::on_add_post_clicked()
{
    string message=ui->messageline->text().toStdString();
    fileoperations *fop=new fileoperations;
    ifstream file("userprofile.txt");
    string user;

    file>>user;

    fop->write_messeage_infile(user,message);

    ui->messageline->setText("Post added successfully!");
}

void userpage::on_searchbtn_clicked()
{
    string user=ui->searchtxt->text().toStdString();
    fileoperations*fop=new fileoperations;
    ifstream file("userprofile.txt");
    string currusername;

    file>>currusername;
    if(fop->isUser(user) && user!=currusername)
    {
        ofstream file("searchuser.txt",ios::trunc);
        file<<user;
        file.close();

        searchpage*up=new searchpage;
        up->show();
    }
    else if(user==currusername)
    {
        ui->searchtxt->setText("You cant search yourself :)");
    }
    else
    {
        ui->searchtxt->setText("User Not Found!");
    }
}

void userpage::on_list_followers_itemDoubleClicked(QListWidgetItem *item)
{
    string user=item->text().toStdString();

    fileoperations fop;
    map<string,string>mp;

    ofstream file("searchuser.txt");

     file<<user;
     file.close();

     followerpage *p=new followerpage;
     p->show();
     this->hide();


}

void userpage::on_list_following_itemDoubleClicked(QListWidgetItem *item)
{
    string user=item->text().toStdString();

    fileoperations fop;
    map<string,string>mp;

    ofstream file("searchuser.txt");

     file<<user;
     file.close();

     followerpage *p=new followerpage;
     p->show();

}

void userpage::on_searchbtn_2_clicked()
{
    Suggestion  *up=new Suggestion();
    up->show();
    this->hide();
}


void userpage::on_pushButton_clicked()
{
    MainWindow *m=new MainWindow();
    m->show();
    hide();
}

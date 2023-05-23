#include "followerpage.h"
#include "ui_followerpage.h"
#include<fileoperations.h>
#include<fstream>
#include<map>

using namespace std;
followerpage::followerpage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::followerpage)
{
    ifstream file("searchuser.txt");
    string user,email;

    file>>user;

    fileoperations fop;
    multimap<string,string>mp;
    map<string,string>ttmp;

    ttmp=fop.read_userandemail_from_file();

    email=ttmp[user];

    ui->setupUi(this);

    ui->userline->setText(QString::fromStdString(user));
    ui->emailline->setText(QString::fromStdString(email));

    mp=fop.read_followers(); //use multimap to prevent search from being O(n)

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

    mp=fop.read_followings();
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

    mp=fop.read_messages();
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

followerpage::~followerpage()
{
    delete ui;
}

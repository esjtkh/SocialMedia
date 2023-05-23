#include "suggestion.h"
#include "ui_suggestion.h"
#include <userpage.h>

Suggestion::Suggestion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Suggestion)
{
    ui->setupUi(this);
    ifstream file("userprofile.txt");
    string user,pass,email;
    file>>user>>pass>>email;
    username=user;
    allperson=fops.read_userandpass_from_file();
    followers = fops.read_followers();
    function();
}

Suggestion::~Suggestion()
{
    delete ui;
}
int Suggestion:: common( string user2)
{
    int common=0;
    auto itr1=followers.lower_bound(username);
    auto itr2=followers.upper_bound(username);
    auto itr3=followers.lower_bound(user2);
    auto itr4=followers.upper_bound(user2);
    for(auto it=itr1;it!=itr2;it++)
    {
       while(itr3!=itr4)
       {
           if(itr3->second==it->second)
               common++;
           itr3++;
       }

    }
    return common;
}
int Suggestion:: uncommon(string user2)
{
    int uncommon=0;
    auto itr1=followers.lower_bound(username);
    auto itr2=followers.upper_bound(username);
    auto itr3=followers.lower_bound(user2);
    auto itr4=followers.upper_bound(user2);
    for(auto it=itr1;it!=itr2;it++)
    {
       while(itr3!=itr4)
       {
           if(itr3->second!=it->second)
               uncommon++;
           itr3++;
       }

    }
    return uncommon;
}
int Suggestion::connection(int common,int uncommon)
{
    if(uncommon!=0)
        return common/uncommon;
    return common;
}
void Suggestion ::function()
{
    auto itr1=followers.lower_bound(username);
    auto itr2=followers.upper_bound(username);
    allperson.erase(username);
    while(itr1!=itr2)
    {
        allperson.erase(itr1->second);
        itr1++;
    }
    vector<Connection> cnn;
    for(auto it=allperson.begin();it!=allperson.end();it++)
    {
        int com=common(it->first);
        int ucom=uncommon(it->first);
        int conn=connection(com,ucom);
        Connection person;
        person.user=it->first;
        person.connection=conn;
        cnn.push_back(person);
    }
    make_heap(cnn.begin(),cnn.end(),comp());
    auto rit = allperson.begin();

    if(cnn.size()>6)
    {
        for(int i=0;i<6;i++)
        {
            if(cnn.front().connection!=0)
            {
                QString qs= QString :: fromStdString(cnn.front().user);
                ui->list_suggestion->addItem(qs);
                cnn.pop_back();
            }
            else
            {
                QString s = QString::fromStdString(rit->first);
                ui->list_suggestion->addItem(s);
                rit++;
            }


        }
    }
    else
        ui->list_suggestion->addItem("NULL");


}

void Suggestion::on_pushButton_clicked()
{
    userpage *up=new userpage();
     up->show();
     this->hide();
}


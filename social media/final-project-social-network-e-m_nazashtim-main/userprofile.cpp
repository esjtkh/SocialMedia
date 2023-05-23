#include "userprofile.h"
#include "ui_userprofile.h"
#include "fileoperations.h"
#include<fstream>
#include<qmessagebox.h>
#include <userpage.h>
#include <log_in.h>
using namespace std;
userprofile::userprofile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::userprofile)
{   
    ifstream file("userprofile.txt");
    string user,pass,email;
    file>>user>>pass>>email;

    ui->setupUi(this);

    ui->usertxt->setText(QString::fromStdString(user));
    ui->passtxt->setText(QString::fromStdString(pass));
    ui->emailtxt->setText(QString::fromStdString(email));
}

userprofile::~userprofile()
{
    delete ui;
}

void userprofile::on_pushButton_2_clicked()
{
    fileoperations fops;
    QString Qusername = ui->usertxt->text();
    QString Qemail= ui->emailtxt->text();
    QString QPass=ui->passtxt->text();
    string pass=QPass.toStdString();
    string email=Qemail.toStdString();
    string username = Qusername.toStdString();
    vector<vector<string>> all_info=fops.read_all_info_from_file();
    for(int i=0;i<all_info.size();i++)
    {
        if(all_info[i][0]==username)
        {
            all_info[i][1]=pass;
            all_info[i][2]=email;
        }
    }
    ofstream file;
    file.open("userinfo.txt",ios::trunc);
    for(int i=0;i<all_info.size();i++)
    {
        file<<all_info[i][0]<<" "<<all_info[i][1]<<" "<<all_info[i][2]<<endl;
    }
    file.close();
    ofstream fprof;
    fprof.open("userprofile.txt",ios::trunc);
    fprof<<username<<" "<<pass<<" "<<email;
    fprof.close();
    userpage *up=new userpage();
     up->show();
     this->hide();
}

void userprofile::on_passtxt_textChanged(const QString &arg1)
{
    ui->pushButton_2->setEnabled(true);
}


void userprofile::on_emailtxt_textChanged(const QString &arg1)
{
     ui->pushButton_2->setEnabled(true);
}


void userprofile::on_pushButton_clicked()
{
    fileoperations fops;
    QString Qusername = ui->usertxt->text();
    QString Qemail= ui->emailtxt->text();
    QString QPass=ui->passtxt->text();
    string pass=QPass.toStdString();
    string email=Qemail.toStdString();
    string username = Qusername.toStdString();
    vector<vector<string>> all_info=fops.read_all_info_from_file();
    int i=0;
    for(auto it=all_info.begin();it< all_info.end();it++)
    {
        if(all_info[i][0]==username)
        {
            all_info.erase(it);
        }
        i++;
    }
    ofstream file;
    file.open("userinfo.txt",ios::trunc);
    for(int i=0;i<all_info.size();i++)
    {
        file<<all_info[i][0]<<" "<<all_info[i][1]<<" "<<all_info[i][2]<<endl;
    }
    file.close();
    multimap<string, string> followers=fops.read_followers();
    followers.erase(username);
    for(auto it=followers.begin();it!=followers.end();it++)
    {
        if(it->second==username)
        {
            //followers.erase(it);
            it->second="Delete acount";
        }
    }
    ofstream folwers;
    folwers.open("followers.txt",ios::trunc);
    for(auto it=followers.begin();it!=followers.end();it++)
    {

        string write=it->first;
        folwers<<write<<" ";
        while(it->first!=write)
        {
            folwers<<it->second<<" ";
            it++;
        }
        folwers<<"end"<<endl;
    }
    folwers.close();
    multimap<string, string> following=fops.read_followings();
    following.erase(username);

    ofstream folloing;
    folloing.open("followings.txt",ios::trunc);
    for(auto it=following.begin();it!=following.end();it++)
    {
        string write=it->first;
        folloing<<write<<" ";
        while(it->first!=write)
        {
            folloing<<it->second<<" ";
            it++;
        }
        folloing<<"end"<<endl;
    }

    folloing.close();
    multimap<string, string> message=fops.read_messages();
    message.erase(username);
    ofstream fmes;
    fmes.open("messages.txt",ios::trunc);
    for(auto it=message.begin();it!=message.end();it++)
    {
         fmes<<it->first<<" "<<it->second<<endl;
    }
    fmes.close();
    log_in *up=new log_in();
     up->show();
     hide();

}


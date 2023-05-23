#include "fileoperations.h"
#include<fstream>
#include<QString>
#include<vector>
#include<map>
using namespace std;
fileoperations::fileoperations()
{

}

bool fileoperations::search(QString user,QString pass)
{
    string us=user.toStdString();
    string pa=pass.toStdString();

    map<string,string>info;
    info=read_userandpass_from_file();

    if(info.count(us))
    {
        if(info[us]==pa)
            return true;
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

}

bool fileoperations::isUnique(QString username,QString pass) //using map feature(not duplicating key)
{

    string us=username.toStdString();
    string pa=pass.toStdString();

    map<string,string>info;
    info=read_userandpass_from_file();

  if(info.count(us))
  {
      return false;
  }
  else
  {
      return true;
  }
}

void fileoperations:: write_to_file(QString username,QString password,QString emailad)
{
    string user=username.toStdString();
    string pass=password.toStdString();
    string email=emailad.toStdString();

    ofstream file("userinfo.txt",ios::app);

    file<<user<<" "<<pass<<" "<<email<<endl;
    file.close();

}

map<string,string> fileoperations::read_userandpass_from_file()
{
    map<string,string>info;
    ifstream file("userinfo.txt");
    string user,pass,email;


    while(file>>user)
    {
       file>>pass>>email;
       info.insert({user,pass});
    }
    file.close();
    return info;
}
map<string,string> fileoperations::read_userandemail_from_file()
{
    map<string,string>info;
    ifstream file("userinfo.txt");
    string user,pass,email;


    while(file>>user)
    {
       file>>pass>>email;
       info.insert({user,email});
    }
    file.close();
    return info;
}
vector<vector<string>> fileoperations::read_all_info_from_file()
{
    vector<vector<string>>vec;

    ifstream file("userinfo.txt");

    string user,pass,email;

    int i=0;

    while(file>>user)
    {
        vec.push_back(vector<string>());
        file>>pass>>email;
        vec[i].push_back(user);
        vec[i].push_back(pass);
        vec[i].push_back(email);
        i++;

    }
    file.close();
    return vec;

}

multimap<string,string>fileoperations:: read_followers()
{
    ifstream file("followers.txt");
    multimap<string,string>mp;
    string user,a,b;
    file>>user;

    while(file>>a)
    {
       if(a!="" && a!="end")
       {
           mp.insert({user,a});
       }
       else if(a=="end")
       {
           file>>user;
       }
    }
    file.close();
    return mp;
}


multimap<string,string>fileoperations:: read_followings()
{
    ifstream file("followings.txt");
    multimap<string,string>mp;
    string user,a,b;
    file>>user;

    while(file>>a)
    {
       if(a!="" && a!="end")
       {
           mp.insert({user,a});
       }
       else if(a=="end")
       {
           file>>user;
       }
    }
    file.close();
    return mp;
}

multimap<string,string> fileoperations::read_messages()
{
    ifstream file("messages.txt");

    multimap<string,string>mp;
    string user,message;

    while(file>>user)
    {
        getline(file,message);
        mp.insert({user,message});
    }
    file.close();
    return mp;
}

void fileoperations::write_messeage_infile(string user,string message)
{
    ofstream file("messages.txt",ios::app);

    file<<user<<" "<<message<<endl;
    file.close();
};

bool fileoperations::isUser(string user)
{
    map<string,string>mp;

    ifstream file("userinfo.txt");

    string username,pass,email;

    while(file>>username)
    {
        file>>pass>>email;

        mp.insert({username,pass});
    }
    file.close();
    if(mp.count(user)!=0)
        return true;
    else
    {
        return false;
    }

}

void fileoperations::addfollowingandfollower(string following,string follower)
{
    multimap<string,string>followers,followings;

    followers=this->read_followers();
    followings=this->read_followings();

    auto itr1=followers.begin();
    auto itr2=followers.end();



    ofstream followersfile("followers.txt",ios::trunc);
    ofstream followingsfile("followings.txt",ios::trunc);

    string username;

//////////////////////////////// write in followers.txt /////////////////////////////////////
    bool state=false;

    if(itr1!=itr2)
    {
        username=itr1->first;

        while(itr1 != itr2)
        {
                if(itr1->first !=following)
                {


                    followersfile<<itr1->first<<" ";

                    while(username==itr1->first)
                    {
                        followersfile<<itr1->second<<" ";
                        itr1++;
                    }

                    followersfile<<"end"<<endl;

                    if(itr1!=itr2)
                    {
                        username=itr1->first;

                    }
                }

                else
                {
                    state=true;
                    followersfile<<itr1->first<<" ";

                    while(username==itr1->first)
                    {
                        followersfile<<itr1->second<<" ";
                        itr1++;
                    }
                    followersfile<<follower<<" "<<"end"<<endl;
                    if(itr1!=itr2)
                    {
                        username=itr1->first;

                    }
                }
        }

        if(state!=true)
        {
            followersfile<<following<<" "<<follower<<" "<<"end"<<endl ;


        }
    }

    else//when map is empty
    {
        followersfile<<following<<" "<<follower<<" "<<"end"<<endl ;
    }


//////////////////////////// write in followings.txt    //////////////////////////////////////////////////

     itr1=followings.begin();
     itr2=followings.end();


     state=false;

    if(itr1!=itr2)
    {
    username=itr1->first;

    while(itr1 != itr2)
    {
            if(itr1->first !=follower)
            {
                followingsfile<<itr1->first<<" ";

                while(username==itr1->first)
                {
                    followingsfile<<itr1->second<<" ";
                    itr1++;
                }

                followingsfile<<"end"<<endl;
                if(itr1!=itr2)
                {
                    username=itr1->first;

                }
            }

            else
            {
                state=true;
                followingsfile<<itr1->first<<" ";

                while(username==itr1->first)
                {
                    followingsfile<<itr1->second<<" ";
                    itr1++;
                }
                followingsfile<<following<<" "<<"end"<<endl;

                if(itr1!=itr2)
                {
                    username=itr1->first;
                }
            }
    }

    if(state!=true)
    {
        followingsfile<<follower<<" "<<following<<" "<<"end"<<endl ;

    }
    }
    else
    {
        followingsfile<<follower<<" "<<following<<" "<<"end"<<endl ;

    }
    followersfile.close();
    followersfile.close();
}

bool fileoperations::check_searcheduser(string following, string follower)
{
    multimap<string,string>followers,followings;

    followers=this->read_followers();
    followings=this->read_followings();

    if(followers.count(following)==1)
    {
        auto tmp1=followers.lower_bound(following);
        auto tmp2=followers.upper_bound(following);

        while(tmp1!=tmp2)
        {
            if(tmp1->second!=follower)
                tmp1++;
            else
            {
                return false;
            }
        }
    }
    return true;
}

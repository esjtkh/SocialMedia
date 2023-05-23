#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H
#include<map>
#include<qstring.h>
#include<vector>
using namespace std;
class fileoperations
{
public:
    fileoperations();
    map<string,string>read_userandpass_from_file();
    map<string,string> read_userandemail_from_file();
    void write_to_file(QString username,QString password,QString emailad);
    bool isUnique(QString username,QString pass);
    bool search(QString user,QString pass);
    vector<vector<string>> read_all_info_from_file();
    multimap<string,string>read_followers();
    multimap<string,string>read_followings();
    multimap<string,string> read_messages();
    void write_messeage_infile(string user,string message);
    bool isUser(string user);
    void addfollowingandfollower(string follower,string following);
    bool check_searcheduser(string following,string follower);
};

#endif // FILEOPERATIONS_H

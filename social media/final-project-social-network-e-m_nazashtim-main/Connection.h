#ifndef CONNECTION_H
#define CONNECTION_H
#include <string>
using namespace std;
class Connection
{
public:
    string user;
    int connection;
};
struct comp
{

    bool operator()(const Connection& s1,const Connection& s2)
    {
        if(s1.connection>=s2.connection)
            return true;
        return false;
    }
};
#endif // CONNECTION_H

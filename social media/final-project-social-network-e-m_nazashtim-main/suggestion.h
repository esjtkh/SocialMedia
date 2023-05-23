#ifndef SUGGESTION_H
#define SUGGESTION_H

#include <QDialog>
#include <string>
#include <fileoperations.h>
#include <map>
#include <fstream>
#include <Connection.h>
using namespace std;

namespace Ui {
class Suggestion;
}

class Suggestion : public QDialog
{
    Q_OBJECT

public:
    fileoperations fops;
    map<string , string> allperson;
    multimap <string , string> followers;
    string username;
    explicit Suggestion(QWidget *parent = nullptr);
    ~Suggestion();
    int common( string user2);
    int uncommon(string user2);
    int connection(int common,int uncommon);
    void function();
private slots:
    void on_pushButton_clicked();

private:
    Ui::Suggestion *ui;
};

#endif // SUGGESTION_H

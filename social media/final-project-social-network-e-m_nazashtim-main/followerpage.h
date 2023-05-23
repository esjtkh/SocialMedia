#ifndef FOLLOWERPAGE_H
#define FOLLOWERPAGE_H

#include <QMainWindow>

namespace Ui {
class followerpage;
}

class followerpage : public QMainWindow
{
    Q_OBJECT

public:
    explicit followerpage(QWidget *parent = nullptr);
    ~followerpage();

private:
    Ui::followerpage *ui;
};

#endif // FOLLOWERPAGE_H

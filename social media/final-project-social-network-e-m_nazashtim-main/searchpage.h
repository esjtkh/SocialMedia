#ifndef SEARCHPAGE_H
#define SEARCHPAGE_H

#include <QMainWindow>

namespace Ui {
class searchpage;
}

class searchpage : public QMainWindow
{
    Q_OBJECT

public:
    explicit searchpage(QWidget *parent = nullptr);
    ~searchpage();

private slots:
    void on_followbtn_clicked();

private:
    Ui::searchpage *ui;
};

#endif // SEARCHPAGE_H

#ifndef USERPAGE_H
#define USERPAGE_H

#include<QListWidget>
#include <QWidget>

namespace Ui {
class userpage;
}

class userpage : public QWidget
{
    Q_OBJECT

public:
    explicit userpage(QWidget *parent = nullptr);
    ~userpage();

private slots:
    void on_pushButton_2_clicked();

    void on_add_post_clicked();

    void on_searchbtn_clicked();

    void on_list_followers_itemDoubleClicked(QListWidgetItem *item);

    void on_list_following_itemDoubleClicked(QListWidgetItem *item);

    void on_searchbtn_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::userpage *ui;
};

#endif // USERPAGE_H

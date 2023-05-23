#ifndef USERPROFILE_H
#define USERPROFILE_H

#include <QWidget>

namespace Ui {
class userprofile;
}

class userprofile : public QWidget
{
    Q_OBJECT

public:
    explicit userprofile(QWidget *parent = nullptr);
    ~userprofile();

private slots:
    void on_pushButton_2_clicked();

    void on_passtxt_textChanged(const QString &arg1);

    void on_emailtxt_textChanged(const QString &arg1);

    void on_pushButton_clicked();

private:
    Ui::userprofile *ui;
};

#endif // USERPROFILE_H

#ifndef SING_UP_H
#define SING_UP_H

#include <QDialog>
#include"fileoperations.h"

namespace Ui {
class sing_up;
}

class sing_up : public QDialog
{
    Q_OBJECT

public:
    explicit sing_up(QWidget *parent = 0);
    ~sing_up();

private slots:
    void on_pushButton_clicked();

private:
    Ui::sing_up *ui;
    fileoperations *f;
};

#endif // SING_UP_H

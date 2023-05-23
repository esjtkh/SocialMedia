#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"sing_up.h"
#include"log_in.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_singup_clicked()
{
    sing_up * page = new sing_up();
    page->show();
    this->close();
}

void MainWindow::on_pushButton_login_clicked()
{
    log_in * page = new log_in();
    page->show();
    this->close();
}

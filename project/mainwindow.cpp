#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "login.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, QColor(249, 222, 201));
    this->setPalette(pal);
    this->setWindowTitle("Auckland Library");

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_member_clicked()
{
    this->hide();
    login* loginPage = new login();
    loginPage->switchPage(0);
    loginPage->setModal(true);
    loginPage->exec();

}


void MainWindow::on_admin_clicked()
{
    this->hide();
    login* loginPage = new login();
    loginPage->switchPage(2);
    loginPage->setModal(true);
    loginPage->exec();
}


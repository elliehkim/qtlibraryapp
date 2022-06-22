#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include "admin.h"
#include "member.h"

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, QColor(249, 222, 201));
    this->setPalette(pal);
    this->setWindowTitle("Login");

    connect(ui->back,SIGNAL(clicked()),this,SLOT(on_backButton_clicked()));
    connect(ui->back_3,SIGNAL(clicked()),this,SLOT(on_backButton_clicked()));


    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("/Users/hyein/database.db");
}

login::~login()
{
    delete ui;
    mydb.close();
}


void login::switchPage(int index){
    ui->stackedWidget->setCurrentIndex(index);
}

void login::on_backButton_clicked(){
    this->hide();
    MainWindow *newmain = new MainWindow();
    newmain->show();
}


void login::on_back_2_clicked()
{
    ui->username->clear();
    ui->password->clear();
    ui->login_status->clear();
    ui->stackedWidget->setCurrentIndex(0);
}

void login::on_memberLogin_clicked()
{
    QString username = ui->username->text().trimmed();
    QString password = ui->password->text().trimmed();

    if(mydb.open()){
        QSqlQuery query;

        query.prepare("SELECT Count(*) FROM members WHERE username = :username AND password = :password");
        query.bindValue(":username",username);
        query.bindValue(":password",password);

        if (query.exec()){
            while(query.next()){
                int numberOfRecord = query.value(0).toInt();
                if(numberOfRecord==1){
                    QMessageBox::information(this,"login","Login Success");
                    this->hide();
                    member *memberPage = new member;
                    memberPage->getUsername(username);
                    memberPage->setModal(true);
                    memberPage->exec();
                }else{
                    ui->login_status->setText("Incorrect Username or Password");
                }
            }

        }
    }

}

void login::on_registration_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void login::on_registerButton_clicked()
{

    QString username = ui->username_2->text().trimmed();
    QString password = ui->password_2->text().trimmed();
    QString name = ui->name->text().trimmed();
    QString email = ui->email->text().trimmed();
    QString phone = ui->phone->text().trimmed();

    if(mydb.open()){

        QSqlQuery query;
        query.prepare("INSERT INTO members (username, password, name, email, phone)"
                      "VALUES (:username, :password,:name, :email, :phone)");
        query.bindValue(":username",username);
        query.bindValue(":password",password);
        query.bindValue(":name",name);
        query.bindValue(":email",email);
        query.bindValue(":phone",phone);

       if(query.exec()){
           QMessageBox::information(this,"Registration","Successfully registered. Pleaase log in");
           ui->stackedWidget->setCurrentIndex(0);
       }
    }
}


void login::on_adminLogin_clicked()
{

    QString password = ui->admin->text().trimmed();

    if(mydb.open()){
        QSqlQuery query;
        query.prepare("SELECT Count(*) FROM admin WHERE password = :password");
        query.bindValue(":password",password);

        if (query.exec()){
            while(query.next()){
            int numberOfRecord = query.value(0).toInt();
                if(numberOfRecord==1){
                    QMessageBox::information(this,"Admin Login","Admin Login Success");
                    this->hide();
                    Admin adminPage;
                    adminPage.setModal(true);
                    adminPage.exec();
                }else{
                    ui->login_status_2->setText("Incorrect Password");
                }
            }
        }
    }
}


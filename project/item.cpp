#include "item.h"
#include "ui_item.h"
#include <string>

item::item(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::item)
{
    ui->setupUi(this);
}

item::~item()
{
    delete ui;
}

int item::getBookID(){
    return this->idBook;
}

int item::getMemberID(){
    return this->idMember;
}
int item::getEnquiriesID(){
    return this->idEnquiries;
}

string item::getBookStatus(){
    return this->status;
}

void item::displayBooks(int idBook, string title, string author, string status){
    this->idBook = idBook;
    this->title = title;
    this->author = author;
    this->status = status;

    ui->id->setText(QString::number(idBook));
    ui->label1->setText(QString::fromStdString(title));
    ui->label2->setText(QString::fromStdString(author));
    ui->label3->setText(QString::fromStdString(status));
}

void item::displayMembers(int idMember, string username, string name){
    this->idMember = idMember;
    this->name = name;
    this->username = username;


    ui->id->setText(QString::number(idMember));
    ui->label4->setText(QString::fromStdString(username));
    ui->label5->setText(QString::fromStdString(name));
}

void item::displayEnquiries(int idEnquiries, string email, string title, string message){
    this->idEnquiries = idEnquiries;
    this->useremail = email;
    this->messageTitle = title;
    this->message = message;

    ui->id->setText(QString::number(idEnquiries));
    ui->label4->setText(QString::fromStdString(messageTitle));
    ui->label6->setText(QString::fromStdString(useremail));
}

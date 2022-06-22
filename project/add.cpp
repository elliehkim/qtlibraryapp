#include "add.h"
#include "ui_add.h"
#include "admin.h"

add::add(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add)
{
    ui->setupUi(this);
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, QColor(249, 222, 201));
    this->setPalette(pal);
    this->setWindowTitle("Add");

    mydb = QSqlDatabase::addDatabase("QSQLITE","second");
    mydb.setDatabaseName("/Users/hyein/database.db");

}

add::~add()
{
    delete ui;
    mydb.close();
}

void add::switchPage(int index){
    ui->stackedWidget->setCurrentIndex(index);
}

void add::on_addBtn_clicked()
{
    QString id = ui->id->text().trimmed();
    QString title = ui->title->text();
    QString author = ui->author->text();
    QString publisher = ui->publisher->text();
    QString edition = ui->edition->text().trimmed();
    QString description = ui->description->toPlainText();


    if(mydb.open()){

        QSqlQuery query;
        query.prepare("INSERT INTO books (id, title, author, publisher, edition, description)"
                      "VALUES (:id, :title,:author, :publisher, :edition,:description)");
        query.bindValue(":id",id);
        query.bindValue(":title",title);
        query.bindValue(":author",author);
        query.bindValue(":publisher",publisher);
        query.bindValue(":edition",edition);
        query.bindValue(":description",description);

        if(query.exec()){
            QMessageBox::information(this,"Add","Successfully added");
            this->close();
        }

    }
}


void add::on_addBtn_2_clicked()
{
    QString username = ui->username->text().trimmed();
    QString password = "0000";
    QString name = ui->name->text();
    QString email = ui->email->text();
    QString phone = ui->phone->text().trimmed();


    if(mydb.open()){

        QSqlQuery query;
        query.prepare("INSERT INTO members (username,password,name,email,phone)"
                      "VALUES (:username, :password,:name, :email, :phone)");
        query.bindValue(":username",username);
        query.bindValue(":password",password);
        query.bindValue(":name",name);
        query.bindValue(":email",email);
        query.bindValue(":phone",phone);

        if(query.exec()){
            QMessageBox::information(this,"Add","Successfully added");
            this->close();
        }
    }
}


void add::on_cancel_2_clicked()
{      this->close();
}


void add::on_cancel_clicked()
{
       this->close();
}


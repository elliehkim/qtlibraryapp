#include "duedetails.h"
#include "ui_duedetails.h"

dueDetails::dueDetails(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dueDetails)
{
    ui->setupUi(this);
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, QColor(249, 222, 201));
    this->setPalette(pal);
    this->setWindowTitle("Details");

    db = QSqlDatabase::addDatabase("QSQLITE","Second");
    db.setDatabaseName("/Users/hyein/database.db");
}

dueDetails::~dueDetails()
{
    delete ui;
    db.close();
}

void dueDetails::getDetails(int bookID, int memberID){
    this->bookID = bookID;
    this->memberID = memberID;

    if(db.open()){
        QSqlQuery query;
        query.prepare("SELECT * FROM books WHERE id = :id");
        query.bindValue(":id",bookID);
        query.exec();

        while(query.next()) {
            QString title = query.value(1).toString();
            QString author = query.value(2).toString();
            QString publisher = query.value(3).toString();
            QString edition = query.value(4).toString();

            ui->bookid->setText(QString::number(bookID));
            ui->title->setText(title);
            ui->author->setText(author);
            ui->publisher->setText(publisher);
            ui->edition->setText(edition);
            }

        QSqlQuery query2;
        query2.prepare("SELECT * FROM members WHERE id = :id");
        query2.bindValue(":id",memberID);
        query2.exec();

        while(query2.next()) {
            QString username = query2.value(1).toString();
            QString name = query2.value(3).toString();
            QString email = query2.value(4).toString();
            QString phone = query2.value(5).toString();

            ui->memberid->setText(QString::number(memberID));
            ui->username->setText(username);
            ui->name->setText(name);
            ui->email->setText(email);
            ui->phone->setText(phone);
            }

        QSqlQuery query3;
        query3.prepare("SELECT actionStatus FROM borrowed where bookID = :bookID");
        query3.bindValue(":bookID",bookID);
        query3.exec();
        while(query3.next()){
            QString status = query3.value(0).toString();

            if(status == "Not Actioned"){
                ui->status->setCurrentIndex(0);
            }else if(status == "Emailed"){
                ui->status->setCurrentIndex(1);
            }else if(status == "Phoned"){
                ui->status->setCurrentIndex(2);
            }
        }

    }

}

void dueDetails::on_pushButton_clicked()
{
    QString newStatus = ui->status->currentText();

    if(db.open()){
        if(newStatus == "Returned"){
            QSqlQuery query;
            query.prepare("DELETE FROM borrowed WHERE bookID = :id");
            query.bindValue(":id",bookID);

            QSqlQuery query2;
            query2.prepare("UPDATE books SET status = 'available' WHERE id = :id");
            query2.bindValue(":id",bookID);

            if(query.exec() && query2.exec()){
                QMessageBox::information(this,"status","book successfully returned");
                this->close();
            }
        }else{
            QSqlQuery query;
            query.prepare("UPDATE borrowed SET actionStatus = '"+newStatus+"' WHERE bookID = :id");
            query.bindValue(":id",bookID);
            if(query.exec()){
               QMessageBox::information(this,"status","Action Status updated");
               this->close();
            }

        }

    }

}


void dueDetails::on_close_clicked()
{
    this->close();
}


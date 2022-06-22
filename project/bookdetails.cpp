#include "bookdetails.h"
#include "ui_bookdetails.h"
#include <QDebug>

bookdetails::bookdetails(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bookdetails)
{
    ui->setupUi(this);
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, QColor(249, 222, 201));
    this->setPalette(pal);
    this->setWindowTitle("Book");

    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(on_close_clicked()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(on_close_clicked()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(on_close_clicked()));
    connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(on_close_clicked()));

    db = QSqlDatabase::addDatabase("QSQLITE","second");
    db.setDatabaseName("/Users/hyein/database.db");

}

bookdetails::~bookdetails()
{
    delete ui;
    db.close();
}


void bookdetails::switchPage(int index){
    ui->stackedWidget->setCurrentIndex(index);
}

void bookdetails::on_close_clicked()
{
    this->close();
}

void bookdetails::getBookDetails(int id)
{
    this->id = id;

    if(db.open()){
        QSqlQuery query;
        query.prepare("SELECT * FROM books WHERE id = :id");
        query.bindValue(":id",id);
        query.exec();

        while (query.next()) {
            this->title = query.value(1).toString();
            this->author = query.value(2).toString();
            this->publisher = query.value(3).toString();
            this->edition = query.value(4).toString();
            this->description = query.value(5).toString();
            this->status = query.value(6).toString();
            }

        ui->id->setText(QString::number(id));
        ui->title->setText(title);
        ui->author->setText(author);
        ui->publisher->setText(publisher);
        ui->edition->setText(edition);
        ui->status->setText(status);
        ui->description->setText(description);


        ui->id_2->setText(QString::number(id));
        ui->title_2->setText(title);
        ui->author_2->setText(author);
        ui->publisher_2->setText(publisher);
        ui->edition_2->setText(edition);
        ui->description_2->setText(description);

        if(status == "available"){
            ui->status_2->setCurrentIndex(0);
            ui->request->setHidden(true);
        }else if(status == "not available"){
            ui->status_2->setCurrentIndex(1);
        }
    }
}


void bookdetails::getMemberDetails(int id)
{
    this->idMember = id;

    if(db.open()){
        QSqlQuery query;
        query.prepare("SELECT * FROM members WHERE id = :id");
        query.bindValue(":id",idMember);
        query.exec();

        while (query.next()) {
            this->username = query.value(1).toString();
            this->name = query.value(3).toString();
            this->email = query.value(4).toString();
            this->phone = query.value(5).toString();
            }

        ui->memberid->setText(QString::number(idMember));
        ui->username->setText(username);
        ui->name->setText(name);
        ui->email->setText(email);
        ui->phone->setText(phone);
    }
}

void bookdetails::getEnquiriesDetails(int id){
    this->idEnquiries = id;

    if(db.open()){
        QSqlQuery query;
        query.prepare("SELECT * FROM enquiries WHERE id = :id");
        query.bindValue(":id",idEnquiries);
        query.exec();

        while (query.next()) {
            this->enquiriesEmail = query.value(1).toString();
            this->enquiriesTitle = query.value(2).toString();
            this->message = query.value(3).toString();
            this->enquiriesStatus = query.value(4).toString();
            }

        ui->enquiriesID->setText(QString::number(idEnquiries));
        ui->enquiriesEmail->setText(enquiriesEmail);
        ui->enquiriesTitle->setText(enquiriesTitle);
        ui->message->setText(message);

        if(enquiriesStatus == "pending"){
            ui->enquiriesStatus->setCurrentIndex(0);
        }else if(enquiriesStatus == "answered"){
            ui->enquiriesStatus->setCurrentIndex(1);
        }
    }

}

void bookdetails::on_edit_clicked()
{
    int newId = ui->id_2->text().toInt();
    QString newTitle = ui->title_2->text();
    QString newAuthor = ui->author_2->text();
    QString newPublisher = ui->publisher_2->text();
    QString newEdition = ui->edition_2->text();
    QString newStatus = ui->status_2->currentText();
    QString newDesc = ui->description_2->toPlainText();


    if(db.open()){
        QSqlQuery query;
        query.prepare("UPDATE books SET id = :newID, title = :title, author = :author, publisher = :publisher, edition = :edition, description = :description, status = :status  WHERE id = :id");
        query.bindValue(":id",id);
        query.bindValue(":title",newTitle);
        query.bindValue(":author",newAuthor);
        query.bindValue(":publisher",newPublisher);
        query.bindValue(":edition",newEdition);
        query.bindValue(":status",newStatus);
        query.bindValue(":description",newDesc);
        query.bindValue(":newID",newId);
        if(query.exec()){
           QMessageBox::information(this,"edit","successfully edited");
           this->close();
        }

    }
}

\

void bookdetails::on_edit_2_clicked()
{
    int newId = ui->memberid->text().toInt();
    QString newUsername = ui->username->text();
    QString newName = ui->name->text();
    QString newPhone = ui->phone->text();
    QString newEmail = ui->email->text();


    if(db.open()){
        QSqlQuery query;
        query.prepare("UPDATE members SET id = :newID , username = '"+newUsername+"', name = '"+newName+"', phone = '"+newPhone+"', email = '"+newEmail+"' WHERE id = :id");
        query.bindValue(":id",idMember);
        query.bindValue(":newID",newId);
        if(query.exec()){
           QMessageBox::information(this,"edit","successfully edited");
           this->close();
        }
    }

}


void bookdetails::on_pushButton_4_clicked()
{
    QString newStatus = ui->enquiriesStatus->currentText();
    if(db.open()){
        QSqlQuery query;
        query.prepare("UPDATE enquiries SET status = '"+newStatus+"' WHERE id = :id");
        query.bindValue(":id",idEnquiries);
        if(query.exec()){
           QMessageBox::information(this,"status","Status updated");
           this->close();
        }
    }
}




void bookdetails::on_request_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->treeWidget->header()->setDefaultAlignment(Qt::AlignCenter);
    ui->treeWidget->clear();

    if(db.open()){
        QSqlQuery query;
        query.prepare("SELECT * FROM request WHERE bookID = :id");
        query.bindValue(":id",id);
        query.exec();
        while (query.next()) {
            int id = query.value(0).toInt();
            int userID = query.value(1).toInt();
            int bookID = query.value(2).toInt();
            QString date = query.value(3).toString();

            QTreeWidgetItem *topLevelItem = new QTreeWidgetItem(ui->treeWidget);
            ui->treeWidget->addTopLevelItem(topLevelItem);
            topLevelItem->setText(0,QString::number(id));
            topLevelItem->setText(1,QString::number(userID));
            topLevelItem->setText(2,QString::number(bookID));
            topLevelItem->setText(3,date);
        }
    }
}


void bookdetails::on_delete_2_clicked()
{
    QTreeWidgetItem *it = ui->treeWidget->currentItem();
    int id = it->text(0).toInt();

    if(db.open()){
        QSqlQuery query;
        query.prepare("DELETE FROM request WHERE id = :id");
        query.bindValue(":id",id);
        query.exec();
    }

    delete it;
}


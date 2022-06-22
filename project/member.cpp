#include "member.h"
#include "ui_member.h"
#include "item.h"
#include "login.h"
#include "mainwindow.h"
#include "bookdetails.h"
#include <QMessageBox>

member::member(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::member)
{
    ui->setupUi(this);
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, QColor(249, 222, 201));
    this->setPalette(pal);
    this->setWindowTitle("Member");
    ui->stackedWidget->setCurrentIndex(0);

    connect(ui->bookList,SIGNAL(clicked()),this,SLOT(bookList_pressed()));
    connect(ui->bookList_2,SIGNAL(clicked()),this,SLOT(bookList_pressed()));
    connect(ui->bookList_3,SIGNAL(clicked()),this,SLOT(bookList_pressed()));
    connect(ui->bookList_4,SIGNAL(clicked()),this,SLOT(bookList_pressed()));

    connect(ui->returnBook,SIGNAL(clicked()),this,SLOT(returnBook_pressed()));
    connect(ui->returnBook_2,SIGNAL(clicked()),this,SLOT(returnBook_pressed()));
    connect(ui->returnBook_3,SIGNAL(clicked()),this,SLOT(returnBook_pressed()));
    connect(ui->returnBook_4,SIGNAL(clicked()),this,SLOT(returnBook_pressed()));

    connect(ui->contact,SIGNAL(clicked()),this,SLOT(contact_pressed()));
    connect(ui->contact_2,SIGNAL(clicked()),this,SLOT(contact_pressed()));
    connect(ui->contact_3,SIGNAL(clicked()),this,SLOT(contact_pressed()));
    connect(ui->contact_4,SIGNAL(clicked()),this,SLOT(contact_pressed()));

    connect(ui->account,SIGNAL(clicked()),this,SLOT(account_pressed()));
    connect(ui->account_2,SIGNAL(clicked()),this,SLOT(account_pressed()));
    connect(ui->account_3,SIGNAL(clicked()),this,SLOT(account_pressed()));
    connect(ui->account_4,SIGNAL(clicked()),this,SLOT(account_pressed()));

    connect(ui->signout,SIGNAL(clicked()),this,SLOT(signout_pressed()));
    connect(ui->signout_2,SIGNAL(clicked()),this,SLOT(signout_pressed()));
    connect(ui->signout_3,SIGNAL(clicked()),this,SLOT(signout_pressed()));
    connect(ui->signout_4,SIGNAL(clicked()),this,SLOT(signout_pressed()));


    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("/Users/hyein/database.db");

    refreshBooks();

}



member::~member()
{
    delete ui;
    mydb.close();

}

void member::getUsername(QString inputUsername){
    this->username = inputUsername;
    if(mydb.open()){
        QSqlQuery query;
        query.prepare("SELECT DISTINCT * FROM members WHERE username = :username");
        query.bindValue(":username",inputUsername);
        query.exec();

        while (query.next()) {
            this->idMember = query.value(0).toInt();
            this->name = query.value(3).toString();
            this->email = query.value(4).toString();
            this->phone = query.value(5).toString();
            }
        ui->memberlabel->setText(username);

    }
}


void member::signout_pressed(){
    this->close();
    MainWindow *newmain = new MainWindow();
    newmain->show();
}


void member::bookList_pressed(){
    ui->stackedWidget->setCurrentIndex(0);
    ui->listWidget->clear();

    refreshBooks();
}

void member::refreshBooks(){
    if(mydb.open()){
        QSqlQuery query;
        query.exec("SELECT * FROM books");

        while(query.next()){
            int id = query.value(0).toInt();
            QString title = query.value(1).toString();
            QString author = query.value(2).toString();
            QString status = query.value(6).toString();

            item* dbItem = new item();
            dbItem->displayBooks(id,title.toStdString(), author.toStdString(), status.toStdString());

            QListWidgetItem *myItem = new QListWidgetItem();
            myItem->setSizeHint(dbItem->sizeHint());
            ui->listWidget->addItem(myItem);
            ui->listWidget->setItemWidget(myItem,dbItem);
        }
    }
}

void member::returnBook_pressed(){
    ui->stackedWidget->setCurrentIndex(1);
    ui->treeWidget->header()->setDefaultAlignment(Qt::AlignCenter);
    ui->treeWidget->setColumnWidth(0,120);
    ui->treeWidget->setColumnWidth(1,230);
    ui->treeWidget->setColumnWidth(2,150);
    ui->treeWidget->setColumnWidth(3,120);
    ui->treeWidget->clear();

    refreshReturn();
}


void member::refreshReturn(){
    if(mydb.open()){
        QSqlQuery query;
        query.prepare("SELECT * FROM borrowed INNER JOIN books ON borrowed.bookID = books.id WHERE userID = :userID");
        query.bindValue(":userID",idMember);
        query.exec();

        while(query.next()){
            int bookId = query.value(1).toInt();
            QString dueDate = query.value(4).toString();
            QString bookTitle = query.value(7).toString();
            QString bookAuthor = query.value(8).toString();

            QTreeWidgetItem *topLevelItem = new QTreeWidgetItem(ui->treeWidget);
            ui->treeWidget->addTopLevelItem(topLevelItem);
            topLevelItem->setText(0,QString::number(bookId));
            topLevelItem->setText(1,bookTitle);
            topLevelItem->setText(2,bookAuthor);
            topLevelItem->setText(3,dueDate);

        }
    }
}
void member::contact_pressed(){
    ui->stackedWidget->setCurrentIndex(2);
}

void member::account_pressed(){
    ui->stackedWidget->setCurrentIndex(3);
    getUsername(username);
    ui->name->setText(name);
    ui->email->setText(email);
    ui->phone->setText(phone);
}

void member::on_submit_clicked()
{
    QString title = ui->title->text();
    QString message = ui->message->toPlainText();

    if(mydb.open()){
        QSqlQuery query;
        query.prepare("INSERT INTO enquiries (email, title, message)"
                      "VALUES (:email, :title, :message)");
        query.bindValue(":email",email);
        query.bindValue(":title",title);
        query.bindValue(":message",message);

        if(query.exec()){
            QMessageBox::information(this,"Submit","enquiry successfully submitted");
            ui->title->setText("");
            ui->message->setText("");
        }

    }
}


void member::on_edit_clicked()
{
    QString newName = ui->name->text();
    QString newEmail = ui->email->text();
    QString newPhone = ui->phone->text();

    if(mydb.open()){
        QSqlQuery query;
           query.exec("UPDATE members SET name = '"+newName+"' , email = '"+newEmail+"', phone = '"+newPhone+"' WHERE username ='"+username+"'");
           if(query.exec()){
           QMessageBox::information(this,"edit","User details successfully edited.");
           }
    }
}


void member::on_save_clicked()
{
    QString newPass = ui->newpass->text();
    QString newPass2 = ui->newpass2->text();

    if(mydb.open()){
        QSqlQuery query;
        if(newPass == newPass2){
            query.exec("UPDATE members SET password = '"+newPass+"' WHERE username ='"+username+"'");
            QMessageBox::information(this,"New Password","Password successfully changed");
            ui->newpass->setText("");
            ui->newpass2->setText("");

        }else{
            QMessageBox::information(this,"Error","passwords do not match");
        }
    }
}




void member::on_view_clicked()
{
    QListWidgetItem* it = ui->listWidget->currentItem();
    item* newItem = dynamic_cast<item*>(ui->listWidget->itemWidget(it));
    int idBook = newItem->getBookID();

    bookdetails *bookPage = new bookdetails;
    bookPage->setModal(true);
    bookPage->switchPage(0);
    bookPage->getBookDetails(idBook);
    bookPage->exec();
}


void member::on_borrow_clicked()
{
    QListWidgetItem* it = ui->listWidget->currentItem();
    item* newItem = dynamic_cast<item*>(ui->listWidget->itemWidget(it));
    int idBook = newItem->getBookID();
    QString bookStatus = QString::fromStdString(newItem->getBookStatus());
    QString status="not available";

    QDate date = QDate::currentDate();
    QString today = date.toString("dd/MM/yyyy");
    QDate newdate = date.addDays(7);
    QString returnDate = newdate.toString("dd/MM/yyyy");

    if(mydb.open()){
        if (bookStatus == "available"){
            QSqlQuery query;
            query.prepare("UPDATE books SET status='"+status+"' WHERE id =:id");
            query.bindValue(":id",idBook);
            query.exec();

            QSqlQuery query2;
            query2.prepare("INSERT INTO borrowed (bookID,userID,borrowedDate, returnDate)"
                           "VALUES (:bookID,:userID,:borrowDate,:returnDate)");
            query2.bindValue(":bookID",idBook);
            query2.bindValue(":userID",idMember);
            query2.bindValue(":borrowDate",today);
            query2.bindValue(":returnDate",returnDate);
            if(query2.exec()){
                QMessageBox::information(this,"borrow","successfully borrowed");
                ui->listWidget->clear();
                refreshBooks();

            }
        }else{
            QMessageBox::information(this,"Error","Sorry, this book is currently not available!");
        }

    }

}


void member::on_return_2_clicked()
{
    QTreeWidgetItem *it = ui->treeWidget->currentItem();
    int bookID = it->text(0).toInt();
    QString status = "available";

    if(mydb.open()){
        QSqlQuery query;
        query.prepare("DELETE FROM borrowed WHERE bookID = :bookID");
        query.bindValue(":bookID",bookID);

        QSqlQuery query2;
        query2.prepare("UPDATE books SET status='"+status+"' WHERE id =:id");
        query2.bindValue(":id",bookID);

        if(query.exec() && query2.exec()){
            QMessageBox::information(this,"return","successfully returned");
            ui->treeWidget->clear();
            refreshReturn();
        }
    }
}


void member::on_request_clicked()
{
    QListWidgetItem* it = ui->listWidget->currentItem();
    item* newItem = dynamic_cast<item*>(ui->listWidget->itemWidget(it));
    int idBook = newItem->getBookID();
    QString bookStatus = QString::fromStdString(newItem->getBookStatus());

    QDate date = QDate::currentDate();
    QString today = date.toString("dd/MM/yyyy");

    if(mydb.open()){
        if(bookStatus == "not available"){
            QSqlQuery query;
            query.prepare("INSERT INTO request (userID,bookID,date)"
                          "VALUES (:userID,:bookID,:date)");
            query.bindValue(":userID",idMember);
            query.bindValue(":bookID",idBook);
            query.bindValue(":date",today);
            if(query.exec()){
            QMessageBox::information(this,"request","Request received! \nYou will get notified once this book is available");
            }
        }else{
            QMessageBox::critical(this,"Error","This book is available");
        }
     }
}


void member::on_searchBtn_clicked()
{
    ui->listWidget->clear();
    int index = ui->comboBox->currentIndex();

    QString value = ui->search->text();
    int id = ui->search->text().toInt();

    if(mydb.open()){
        if(index == 0){
            QSqlQuery query;
            query.prepare("SELECT * FROM books WHERE id =:id");
            query.bindValue(":id",id);
            query.exec();
            while(query.next()){
                int id = query.value(0).toInt();
                QString title = query.value(1).toString();
                QString author = query.value(2).toString();
                QString status = query.value(6).toString();

                item* dbItem = new item();
                dbItem->displayBooks(id,title.toStdString(), author.toStdString(), status.toStdString());

                QListWidgetItem *myItem = new QListWidgetItem();
                myItem->setSizeHint(dbItem->sizeHint());
                ui->listWidget->addItem(myItem);
                ui->listWidget->setItemWidget(myItem,dbItem);
            }
        }else{
            QSqlQuery query;
            query.exec("SELECT * FROM books WHERE title LIKE  '%"+value+"%' or author LIKE  '%"+value+"%'");
            while(query.next()){
                int id = query.value(0).toInt();
                QString title = query.value(1).toString();
                QString author = query.value(2).toString();
                QString status = query.value(6).toString();

                item* dbItem = new item();
                dbItem->displayBooks(id,title.toStdString(), author.toStdString(), status.toStdString());

                QListWidgetItem *myItem = new QListWidgetItem();
                myItem->setSizeHint(dbItem->sizeHint());
                ui->listWidget->addItem(myItem);
                ui->listWidget->setItemWidget(myItem,dbItem);
            }
        }

    }
}


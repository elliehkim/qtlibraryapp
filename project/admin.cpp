#include "admin.h"
#include "ui_admin.h"
#include "mainwindow.h"
#include "item.h"
#include "add.h"
#include "bookdetails.h"
#include "duedetails.h"

using namespace std;

Admin::Admin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, QColor(249, 222, 201));
    this->setPalette(pal);
    this->setWindowTitle("Admin");
    ui->stackedWidget->setCurrentIndex(0);

    connect(ui->books_1,SIGNAL(clicked()),this,SLOT(booksButton_pressed()));
    connect(ui->books_2,SIGNAL(clicked()),this,SLOT(booksButton_pressed()));
    connect(ui->books_3,SIGNAL(clicked()),this,SLOT(booksButton_pressed()));
    connect(ui->books_4,SIGNAL(clicked()),this,SLOT(booksButton_pressed()));
    connect(ui->books_5,SIGNAL(clicked()),this,SLOT(booksButton_pressed()));

    connect(ui->members_1,SIGNAL(clicked()),this,SLOT(membersButton_pressed()));
    connect(ui->members_2,SIGNAL(clicked()),this,SLOT(membersButton_pressed()));
    connect(ui->members_3,SIGNAL(clicked()),this,SLOT(membersButton_pressed()));
    connect(ui->members_4,SIGNAL(clicked()),this,SLOT(membersButton_pressed()));
    connect(ui->members_5,SIGNAL(clicked()),this,SLOT(membersButton_pressed()));

    connect(ui->enquiries_1,SIGNAL(clicked()),this,SLOT(enquiriesButton_pressed()));
    connect(ui->enquiries_2,SIGNAL(clicked()),this,SLOT(enquiriesButton_pressed()));
    connect(ui->enquiries_3,SIGNAL(clicked()),this,SLOT(enquiriesButton_pressed()));
    connect(ui->enquiries_4,SIGNAL(clicked()),this,SLOT(enquiriesButton_pressed()));
    connect(ui->enquiries_5,SIGNAL(clicked()),this,SLOT(enquiriesButton_pressed()));

    connect(ui->account_1,SIGNAL(clicked()),this,SLOT(accountButton_pressed()));
    connect(ui->account_2,SIGNAL(clicked()),this,SLOT(accountButton_pressed()));
    connect(ui->account_3,SIGNAL(clicked()),this,SLOT(accountButton_pressed()));
    connect(ui->account_4,SIGNAL(clicked()),this,SLOT(accountButton_pressed()));
    connect(ui->account_5,SIGNAL(clicked()),this,SLOT(accountButton_pressed()));

    connect(ui->signout,SIGNAL(clicked()),this,SLOT(signout_pressed()));
    connect(ui->signout_2,SIGNAL(clicked()),this,SLOT(signout_pressed()));
    connect(ui->signout_3,SIGNAL(clicked()),this,SLOT(signout_pressed()));
    connect(ui->signout_4,SIGNAL(clicked()),this,SLOT(signout_pressed()));
    connect(ui->signout_5,SIGNAL(clicked()),this,SLOT(signout_pressed()));

    connect(ui->bookStatus,SIGNAL(clicked()),this,SLOT(bookStatusButton_pressed()));
    connect(ui->bookStatus_2,SIGNAL(clicked()),this,SLOT(bookStatusButton_pressed()));
    connect(ui->bookStatus_3,SIGNAL(clicked()),this,SLOT(bookStatusButton_pressed()));
    connect(ui->bookStatus_4,SIGNAL(clicked()),this,SLOT(bookStatusButton_pressed()));
    connect(ui->bookStatus_5,SIGNAL(clicked()),this,SLOT(bookStatusButton_pressed()));


    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("/Users/hyein/database.db");
    refreshBooks();
}


Admin::~Admin()
{
    delete ui;
    mydb.close();
}


void Admin::switchPage(int index){
    ui->stackedWidget->setCurrentIndex(index);
}

void Admin::signout_pressed(){
    this->close();
    MainWindow *newmain = new MainWindow();
    newmain->show();
}

void Admin::refreshBooks(){
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


void Admin::refreshMembers(){
    if(mydb.open()){
        QSqlQuery query;
        query.exec("SELECT id, username, name, email, phone FROM members");

        while(query.next()){
            int id = query.value(0).toInt();
            QString username = query.value(1).toString();
            QString name = query.value(2).toString();

            item* dbItem = new item();
            dbItem->displayMembers(id,username.toStdString(), name.toStdString());

            QListWidgetItem *myItem = new QListWidgetItem();
            myItem->setSizeHint(dbItem->sizeHint());
            ui->listWidget_2->addItem(myItem);
            ui->listWidget_2->setItemWidget(myItem,dbItem);

        }
    }
}

void Admin::booksButton_pressed()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->listWidget->clear();
    refreshBooks();
}


void Admin::membersButton_pressed()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->listWidget_2->clear();

    refreshMembers();
}


void Admin::bookStatusButton_pressed(){

    ui->stackedWidget->setCurrentIndex(2);
    ui->treeWidget->header()->setDefaultAlignment(Qt::AlignCenter);
    ui->treeWidget->setColumnWidth(0,80);
    ui->treeWidget->setColumnWidth(1,200);
    ui->treeWidget->setColumnWidth(2,120);
    ui->treeWidget->setColumnWidth(3,80);
    ui->treeWidget->setColumnWidth(4,100);
    ui->treeWidget->setColumnWidth(5,90);
    ui->treeWidget->clear();

    ui->treeWidget_2->header()->setDefaultAlignment(Qt::AlignCenter);
    ui->treeWidget_2->setColumnWidth(0,80);
    ui->treeWidget_2->setColumnWidth(1,200);
    ui->treeWidget_2->setColumnWidth(2,120);
    ui->treeWidget_2->setColumnWidth(3,80);
    ui->treeWidget_2->setColumnWidth(4,100);
    ui->treeWidget_2->setColumnWidth(5,90);
    ui->treeWidget_2->clear();

    refreshdueDates();
}


void Admin::refreshdueDates(){
    if(mydb.open()){
        QSqlQuery query;
        query.exec("SELECT * FROM borrowed INNER JOIN books ON borrowed.bookID = books.id");

        while(query.next()){
            int bookId = query.value(1).toInt();
            int userId = query.value(2).toInt();
            QString dueDate = query.value(4).toString();
            QString actionStatus = query.value(5).toString();
            QString bookTitle = query.value(7).toString();
            QString bookAuthor = query.value(8).toString();
            QDate date1 = QDate::fromString(dueDate,"dd/MM/yyyy");
            QDate date2 = QDate::currentDate();

            if(date1>date2){
                QTreeWidgetItem *topLevelItem = new QTreeWidgetItem(ui->treeWidget);
                ui->treeWidget->addTopLevelItem(topLevelItem);
                topLevelItem->setText(0,QString::number(bookId));
                topLevelItem->setText(1,bookTitle);
                topLevelItem->setText(2,bookAuthor);
                topLevelItem->setText(3,QString::number(userId));
                topLevelItem->setText(4,dueDate);
                topLevelItem->setText(5,actionStatus);
            }else{
                QTreeWidgetItem *topLevelItem = new QTreeWidgetItem(ui->treeWidget_2);
                ui->treeWidget_2->addTopLevelItem(topLevelItem);
                topLevelItem->setText(0,QString::number(bookId));
                topLevelItem->setText(1,bookTitle);
                topLevelItem->setText(2,bookAuthor);
                topLevelItem->setText(3,QString::number(userId));
                topLevelItem->setText(4,dueDate);
                topLevelItem->setText(5,actionStatus);
            }


        }
    }
}

void Admin::enquiriesButton_pressed()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->listWidget_3->clear();

    if(mydb.open()){
        QSqlQuery query;
        query.exec("SELECT id, email, title, message FROM enquiries");

        while(query.next()){
            int id = query.value(0).toInt();
            QString email = query.value(1).toString();
            QString title = query.value(2).toString();
            QString message = query.value(3).toString();

            item* dbItem = new item();
            dbItem->displayEnquiries(id,email.toStdString(), title.toStdString(), message.toStdString());

            QListWidgetItem *myItem = new QListWidgetItem();
            myItem->setSizeHint(dbItem->sizeHint());
            ui->listWidget_3->addItem(myItem);
            ui->listWidget_3->setItemWidget(myItem,dbItem);
        }
    }
}


void Admin::accountButton_pressed()
{
    ui->stackedWidget->setCurrentIndex(4);
}


void Admin::on_add_clicked()
{
    add *addPage = new add;
    addPage->setModal(true);
    addPage->switchPage(0);
    addPage->exec();

    if(addPage->close()){
        ui->listWidget->clear();
        refreshBooks();
    }
}


void Admin::on_add_2_clicked()
{
    add *addPage = new add;
    addPage->setModal(true);
    addPage->switchPage(1);
    addPage->exec();

    if(addPage->close()){
        ui->listWidget_2->clear();
        refreshMembers();
    }
}


void Admin::on_del_clicked()
{
    QListWidgetItem* it = ui->listWidget->currentItem();
    item* newItem = dynamic_cast<item*>(ui->listWidget->itemWidget(it));
    int id = newItem->getBookID();

    if(mydb.open()){
        QSqlQuery query;
        query.prepare("DELETE FROM books WHERE id = :id");
        query.bindValue(":id",id);
        query.exec();
    }
    delete it;
}


void Admin::on_del_2_clicked()
{
    QListWidgetItem *it = ui->listWidget_2->currentItem();
    item* newItem = dynamic_cast<item*>(ui->listWidget_2->itemWidget(it));
    int id = newItem->getMemberID();

    if(mydb.open()){
        QSqlQuery query;
        query.prepare("DELETE FROM members WHERE id = :id");
        query.bindValue(":id",id);
        query.exec();
    }
    delete it;
}


void Admin::on_save_clicked()
{
    QString newPass = ui->newpassword->text();
    QString newPass2 = ui->newpassword_2->text();

    if(mydb.open()){
        QSqlQuery query;
        if(newPass == newPass2){
            query.exec("UPDATE admin SET password = '"+newPass+"'");
            QMessageBox::information(this,"New Password","Password successfully changed");
            ui->newpassword->setText("");
            ui->newpassword_2->setText("");

        }else{
            QMessageBox::information(this,"Error","passwords do not match");
        }
    }
}


void Admin::on_viewBooks_clicked()
{
    QListWidgetItem* it = ui->listWidget->currentItem();
    item* newItem = dynamic_cast<item*>(ui->listWidget->itemWidget(it));
    int id = newItem->getBookID();

    bookdetails *bookPage = new bookdetails;
    bookPage->setModal(true);
    bookPage->switchPage(1);
    bookPage->getBookDetails(id);
    bookPage->exec();

    if(bookPage->close()){
        ui->listWidget->clear();
        refreshBooks();
    }
}


void Admin::on_viewMebers_clicked()
{
    QListWidgetItem* it = ui->listWidget_2->currentItem();
    item* newItem = dynamic_cast<item*>(ui->listWidget_2->itemWidget(it));
    int id = newItem->getMemberID();

    bookdetails *bookPage = new bookdetails;
    bookPage->setModal(true);
    bookPage->switchPage(2);
    bookPage->getMemberDetails(id);
    bookPage->exec();

    if(bookPage->close()){
        ui->listWidget_2->clear();
        refreshMembers();
    }
}


void Admin::on_view_clicked()
{
    QListWidgetItem* it = ui->listWidget_3->currentItem();
    item* newItem = dynamic_cast<item*>(ui->listWidget_3->itemWidget(it));
    int id = newItem->getEnquiriesID();

    bookdetails *bookPage = new bookdetails;
    bookPage->setModal(true);
    bookPage->switchPage(3);
    bookPage->getEnquiriesDetails(id);
    bookPage->exec();
}



void Admin::on_viewDetails_clicked()
{
    QTreeWidgetItem *it = ui->treeWidget->currentItem();
    int bookID = it->text(0).toInt();
    int userID = it->text(3).toInt();

    dueDetails *dueDetailPage = new dueDetails;
    dueDetailPage->setModal(true);
    dueDetailPage->getDetails(bookID, userID);
    dueDetailPage->exec();

    if(dueDetailPage->close()){
        ui->treeWidget->clear();
        ui->treeWidget_2->clear();
        refreshdueDates();
    }
}


void Admin::on_viewDetails_2_clicked()
{
    QTreeWidgetItem *it = ui->treeWidget_2->currentItem();
    int bookID = it->text(0).toInt();
    int userID = it->text(3).toInt();

    dueDetails *dueDetailPage = new dueDetails;
    dueDetailPage->setModal(true);
    dueDetailPage->getDetails(bookID, userID);
    dueDetailPage->exec();

    if(dueDetailPage->close()){
        ui->treeWidget->clear();
        ui->treeWidget_2->clear();
        refreshdueDates();
    }
}


void Admin::on_searchBtn_clicked()
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


void Admin::on_searchBtn_2_clicked()
{
    ui->listWidget_2->clear();
    int index = ui->comboBox_2->currentIndex();

    QString value = ui->search_2->text();
    int id = ui->search_2->text().toInt();

    if(mydb.open()){
        if(index == 0){
            QSqlQuery query;
            query.prepare("SELECT * FROM members WHERE id =:id");
            query.bindValue(":id",id);
            query.exec();
            while(query.next()){
                int id = query.value(0).toInt();
                QString username = query.value(1).toString();
                QString name = query.value(3).toString();

                item* dbItem = new item();
                dbItem->displayMembers(id,username.toStdString(), name.toStdString());

                QListWidgetItem *myItem = new QListWidgetItem();
                myItem->setSizeHint(dbItem->sizeHint());
                ui->listWidget_2->addItem(myItem);
                ui->listWidget_2->setItemWidget(myItem,dbItem);

            }
        }else{
            QSqlQuery query;
            query.exec("SELECT * FROM members WHERE username LIKE  '%"+value+"%'");
            while(query.next()){
                int id = query.value(0).toInt();
                QString username = query.value(1).toString();
                QString name = query.value(3).toString();

                item* dbItem = new item();
                dbItem->displayMembers(id,username.toStdString(), name.toStdString());

                QListWidgetItem *myItem = new QListWidgetItem();
                myItem->setSizeHint(dbItem->sizeHint());
                ui->listWidget_2->addItem(myItem);
                ui->listWidget_2->setItemWidget(myItem,dbItem);
            }
        }

    }
}


#ifndef BOOKDETAILS_H
#define BOOKDETAILS_H

#include "admin.h"

#include <QDialog>
#include <QtSql>
#include <QString>
#include <QSqlQuery>
#include <QFileInfo>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QDir>

using namespace std;

namespace Ui {
class bookdetails;
}

class bookdetails : public QDialog
{
    Q_OBJECT

public:
    explicit bookdetails(QWidget *parent = nullptr);
    ~bookdetails();
    void getBookDetails(int id);
    void getMemberDetails(int id);
    void getEnquiriesDetails(int id);
    void switchPage(int index);

private slots:
    void on_close_clicked();

    void on_edit_clicked();

    void on_edit_2_clicked();

    void on_pushButton_4_clicked();

    void on_request_clicked();

    void on_delete_2_clicked();

private:
    Ui::bookdetails *ui;

    //Book Details
    int id;
    QString title;
    QString author;
    QString publisher;
    QString edition;
    QString status;
    QString description;

    //Member Details
    int idMember;
    QString username;
    QString name;
    QString phone;
    QString email;

    //Enquiries Details
    int idEnquiries;
    QString enquiriesEmail;
    QString enquiriesTitle;
    QString message;
    QString enquiriesStatus;


    QSqlDatabase db;
};

#endif // BOOKDETAILS_H

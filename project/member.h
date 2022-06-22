#ifndef MEMBER_H
#define MEMBER_H

#include <QVector>
#include <QDialog>
#include <QPushButton>
#include <QtSql>
#include <QString>
#include <QSqlQuery>
#include <QtDebug>
#include <QFileInfo>
#include <QSqlDatabase>
#include <QDir>

using namespace std;


namespace Ui {
class member;
}

class member : public QDialog
{
    Q_OBJECT

public:
    explicit member(QWidget *parent = nullptr);
    ~member();

    void getUsername(QString inputUsername);
    void setUsername(QString username);
    void refreshReturn();
    void refreshBooks();


    QString username;
    int idMember;
    QString phone;
    QString email;
    QString name;
    QString status;

private slots:

    void bookList_pressed();
    void returnBook_pressed();
    void contact_pressed();
    void account_pressed();
    void on_submit_clicked();
    void on_edit_clicked();
    void on_save_clicked();
    void signout_pressed();


    void on_view_clicked();

    void on_borrow_clicked();

    void on_return_2_clicked();

    void on_request_clicked();

    void on_searchBtn_clicked();

private:
    Ui::member *ui;
    QSqlDatabase mydb;

};

#endif // MEMBER_H

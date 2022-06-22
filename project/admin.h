#ifndef ADMIN_H
#define ADMIN_H

#include "bookdetails.h"
#include <QDialog>
#include <QPushButton>
#include <QtSql>
#include <QString>
#include <QSqlQuery>
#include <QtDebug>
#include <QFileInfo>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QDebug>
#include <QDir>


namespace Ui {
class Admin;
}

class Admin : public QDialog
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = nullptr);
    ~Admin();
    void switchPage(int index);
    void refreshBooks();
    void refreshMembers();
    void refreshdueDates();


private slots:

    void booksButton_pressed();

    void membersButton_pressed();

    void bookStatusButton_pressed();

    void enquiriesButton_pressed();

    void accountButton_pressed();

    void on_add_clicked();

    void on_add_2_clicked();

    void on_del_clicked();

    void on_del_2_clicked();

    void on_save_clicked();

    void on_viewBooks_clicked();

    void signout_pressed();

    void on_viewMebers_clicked();

    void on_view_clicked();

    void on_viewDetails_clicked();

    void on_viewDetails_2_clicked();

    void on_searchBtn_clicked();

    void on_searchBtn_2_clicked();

private:
    Ui::Admin *ui;
    QSqlDatabase mydb;

};


#endif // ADMIN_H

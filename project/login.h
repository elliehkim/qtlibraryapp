#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QtSql>
#include <QString>
#include <QSqlQuery>
#include <QtDebug>
#include <QFileInfo>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QDir>

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    void switchPage(int index);

private slots:
    void on_memberLogin_clicked();

    void on_registerButton_clicked();

    void on_registration_clicked();

    void on_backButton_clicked();

    void on_back_2_clicked();

    void on_adminLogin_clicked();

private:
    Ui::login *ui;
    QSqlDatabase mydb;

};

#endif // LOGIN_H

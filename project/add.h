#ifndef ADD_H
#define ADD_H

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
class add;
}

class add : public QDialog
{
    Q_OBJECT

public:
    explicit add(QWidget *parent = nullptr);
    ~add();
    void switchPage(int index);

private slots:
    void on_addBtn_clicked();

    void on_addBtn_2_clicked();

    void on_cancel_2_clicked();

    void on_cancel_clicked();

private:
    Ui::add *ui;
    QSqlDatabase mydb;

};

#endif // ADD_H

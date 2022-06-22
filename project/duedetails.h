#ifndef DUEDETAILS_H
#define DUEDETAILS_H

#include <QDialog>
#include <QtSql>
#include <QString>
#include <QSqlQuery>
#include <QFileInfo>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QDir>

namespace Ui {
class dueDetails;
}

class dueDetails : public QDialog
{
    Q_OBJECT

public:
    explicit dueDetails(QWidget *parent = nullptr);
    ~dueDetails();

    void getDetails(int bookID, int memberID);

private slots:
    void on_pushButton_clicked();

    void on_close_clicked();

private:
    Ui::dueDetails *ui;
    int bookID;
    int memberID;
    QSqlDatabase db;
};

#endif // DUEDETAILS_H

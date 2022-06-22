#ifndef ITEM_H
#define ITEM_H

#include <QWidget>
#include <string>

using namespace std;

namespace Ui {
class item;
}

class item : public QWidget
{
    Q_OBJECT

public:
    explicit item(QWidget *parent = nullptr);
    ~item();
    void displayBooks(int id, string title, string author, string status);
    void displayMembers(int id, string username, string name);
    void displayEnquiries(int id,string email, string title, string message);

    int getBookID();
    int getMemberID();
    int getEnquiriesID();
    string getBookStatus();

private:
    Ui::item *ui;
    int idBook;
    string title;
    string author;
    string status;

    int idMember;
    string name;
    string username;
    string email;
    string phone;

    int idEnquiries;
    string useremail;
    string messageTitle;
    string message;

};

#endif // ITEM_H

#include "details.h"
#include "ui_details.h"

details::details(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::details)
{
    ui->setupUi(this);
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, QColor(249, 222, 201));
    this->setPalette(pal);
    this->setWindowTitle("Details");
}

details::~details()
{
    delete ui;
}

#include "dialog.h"
#include "ui_dialog.h"
#include "login.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    login conn;
    if(!conn.connOpen()){
        ui -> label_8 -> setText("Database is not connected...");
    }else{
        ui -> label_8 -> setText("Database is connected...");
    }
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{

}


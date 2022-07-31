#include "login.h"
#include "ui_login.h"
#include "dialog.h"
#include "dialog1.h"
login::login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);

    myDb = QSqlDatabase::addDatabase("QSQLITE");
    myDb.setDatabaseName("C:/sqlite/database.db");
    if(!myDb.open()){
        ui -> label -> setText("Database is not connected...");
    }else{
        ui -> label -> setText("Database is connected...");
    }
}

login::~login()
{
    delete ui;
}


void login::on_pushButton_clicked()
{
QString username, password;
username = ui -> lineEdit_username -> text();
password = ui ->lineEdit_Password ->text();

if(!myDb.isOpen()){
    qDebug()<<"Failed to poen the database";
    return;
}
QSqlQuery qry;
if(qry.exec(" select * from employee where username = '"+username+"' and password = '"+password+"'")){
   int count = 0;
    while(qry.next()){
       count ++;
   }
    if(count == 1){

        if(username == "2" && password == "2")//for admin + new dialog
        {
            this -> hide();//it will hide the current page and open new page
            Dialog1 dialog1;
            dialog1.setModal(true);
            dialog1.exec();
        }
        else{
        ui -> label_2 -> setText("username and password is correct");
        this -> hide();//it will hide the current page and open new page
        Dialog dialog;
        dialog.setModal(true);
        dialog.exec();
        }
    }
    if(count > 1){
        ui -> label_2 -> setText("username and password is duplicated");
    }
    if(count < 1){
        ui -> label_2 -> setText("username and password is not correct");
    }
}
}


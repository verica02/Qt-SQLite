#include "dialog.h"
#include "ui_dialog.h"
#include "login.h"
#include <QMessageBox>
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    login conn;//connection of atabase with second form
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

//saving data
void Dialog::on_pushButton_clicked()
{
   login conn;
    QString eid, name, surname, age;
   eid = ui ->lineEdit_id -> text();
   name = ui ->lineEdit_name -> text();
   surname = ui ->lineEdit_surname -> text();
   age = ui ->lineEdit_age -> text();

    if(!conn.connOpen()){
        qDebug()<<"Failed to open the database";
        return;
    }

    QSqlQuery qry;
    qry.prepare("insert into employee (eid,name,surname,age) values ('"+eid+"', '"+name+"', '"+surname+"', '"+age+"')");

    if(qry.exec()){
       QMessageBox::information(this, tr("Save"), tr("Data is saved"));
    conn.connClose();
    }else{
        QMessageBox::information(this, tr("error::"),qry.lastError().text());
    }
}

//edit data
void Dialog::on_pushButton_edit_clicked()
{
    login conn;
     QString eid, name, surname, age;
    eid = ui ->lineEdit_id -> text();
    name = ui ->lineEdit_name -> text();
    surname = ui ->lineEdit_surname -> text();
    age = ui ->lineEdit_age -> text();

     if(!conn.connOpen()){
         qDebug()<<"Failed to open the database";
         return;
     }

     QSqlQuery qry;
     qry.prepare("update employee set eid='"+eid+"', name='"+name+"', surname='"+surname+"', age='"+age+"'where eid='"+eid+"'");

     if(qry.exec()){
        QMessageBox::information(this, tr("Edit"), tr("Data is updated"));
     conn.connClose();
     }else{
         QMessageBox::information(this, tr("error::"),qry.lastError().text());
     }
}

//delete data
void Dialog::on_pushButton_2_clicked()
{
    login conn;
     QString eid;// name, surname, age;
    eid = ui ->lineEdit_id -> text();
//    name = ui ->lineEdit_name -> text();
//    surname = ui ->lineEdit_surname -> text();
//    age = ui ->lineEdit_age -> text();

     if(!conn.connOpen()){
         qDebug()<<"Failed to open the database";
         return;
     }

     QSqlQuery qry;
     qry.prepare("Delete from employee where eid ='"+eid+"'");

     if(qry.exec()){
        QMessageBox::critical(this, tr("Delete"), tr("Data is deleted"));
     conn.connClose();
     }else{
         QMessageBox::critical(this, tr("error::"),qry.lastError().text());
     }
}

//load data
void Dialog::on_pushButton_load_clicked()
{
   login conn;
   QSqlQueryModel *modal = new QSqlQueryModel();
   conn.connOpen();
   QSqlQuery *qry = new QSqlQuery(conn.myDb);
   qry -> prepare("select eid, name, surname from employee");
   qry -> exec();
   modal -> setQuery(*qry);
   ui -> tableView -> setModel(modal);
   conn.connClose();
   qDebug() << (modal -> rowCount());
}

//load list
void Dialog::on_pushButton_load_list_clicked()
{
    login conn;
    QSqlQueryModel *modal = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qry = new QSqlQuery(conn.myDb);
    qry -> prepare("select name from employee");//listView has only one column
    qry -> exec();
    modal -> setQuery(*qry);

    ui -> listView -> setModel(modal);
    ui -> comboBox -> setModel(modal);

    conn.connClose();
    qDebug() << (modal -> rowCount());
}

//comboBox
void Dialog::on_comboBox_currentTextChanged(const QString &arg1)
{
    QString name = ui ->comboBox ->currentText();
    login conn;
     if(!conn.connOpen()){
         qDebug()<<"Failed to open the database";
         return;
     }
     conn.connOpen();
     QSqlQuery qry;
     qry.prepare("select * from employee where name = '"+name+"'");
//     eid = ui ->lineEdit_id -> text();
//     name = ui ->lineEdit_name -> text();
//     surname = ui ->lineEdit_surname -> text();
//     age = ui ->lineEdit_age -> text();
     if(qry.exec()){
        while(qry.next()){
          ui -> lineEdit_id -> setText(qry.value(0).toString());//0 for the first column id
          ui -> lineEdit_name -> setText(qry.value(1).toString());
          ui -> lineEdit_surname -> setText(qry.value(2).toString());
          ui -> lineEdit_age -> setText(qry.value(3).toString());
        }
     conn.connClose();
     }

     else{
         QMessageBox::information(this, tr("error::"),qry.lastError().text());
     }
}

//table
void Dialog::on_tableView_activated(const QModelIndex &index)
{
    QString val = ui -> tableView -> model() -> data(index).toString();
    login conn;
     if(!conn.connOpen()){
         qDebug()<<"Failed to open the database";
         return;
     }
     conn.connOpen();
     QSqlQuery qry;
     qry.prepare("select * from employee where eid = '"+val+"' or name = '"+val+"' or surname = '"+val+"' or age = '"+val+"'");
//     eid = ui ->lineEdit_id -> text();
//     name = ui ->lineEdit_name -> text();
//     surname = ui ->lineEdit_surname -> text();
//     age = ui ->lineEdit_age -> text();
     if(qry.exec()){
        while(qry.next()){
          ui -> lineEdit_id -> setText(qry.value(0).toString());//0 for the first column id
          ui -> lineEdit_name -> setText(qry.value(1).toString());
          ui -> lineEdit_surname -> setText(qry.value(2).toString());
          ui -> lineEdit_age -> setText(qry.value(3).toString());
        }
     conn.connClose();
     }

     else{
         QMessageBox::information(this, tr("error::"),qry.lastError().text());
     }
}


void Dialog::on_listView_activated(const QModelIndex &index)
{
    QString val = ui -> listView -> model() -> data(index).toString();
    login conn;
     if(!conn.connOpen()){
         qDebug()<<"Failed to open the database";
         return;
     }
     conn.connOpen();
     QSqlQuery qry;
     qry.prepare("select * from employee where eid = '"+val+"' or name = '"+val+"' or surname = '"+val+"' or age = '"+val+"'");
//     eid = ui ->lineEdit_id -> text();
//     name = ui ->lineEdit_name -> text();
//     surname = ui ->lineEdit_surname -> text();
//     age = ui ->lineEdit_age -> text();
     if(qry.exec()){
        while(qry.next()){
          ui -> lineEdit_id -> setText(qry.value(0).toString());//0 for the first column id
          ui -> lineEdit_name -> setText(qry.value(1).toString());
          ui -> lineEdit_surname -> setText(qry.value(2).toString());
          ui -> lineEdit_age -> setText(qry.value(3).toString());
        }
     conn.connClose();
     }

     else{
         QMessageBox::information(this, tr("error::"),qry.lastError().text());
     }
}


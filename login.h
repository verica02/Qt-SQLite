#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include "dialog.h"
//#include "dialog1.h"

QT_BEGIN_NAMESPACE
namespace Ui { class login; }
QT_END_NAMESPACE

class login : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase myDb;

    void connClose(){
       myDb.close();//closing database and removing any default connection
       myDb.removeDatabase(QSqlDatabase::defaultConnection);
    }

    bool connOpen(){

        myDb = QSqlDatabase::addDatabase("QSQLITE");
        myDb.setDatabaseName("C:/sqlite/database.db");
        if(!myDb.open()){
           qDebug()<<"Database is not connected...";
           return false;
        }else{
           qDebug()<<"Database is connected...";
           return true;
    }
    }


public:
    login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_pushButton_clicked();

private:
    Ui::login *ui;


};
#endif // LOGIN_H

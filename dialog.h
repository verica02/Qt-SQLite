#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_edit_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_load_clicked();

    void on_pushButton_load_list_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H

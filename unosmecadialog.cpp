#include "unosmecadialog.h"
#include "ui_unosmecadialog.h"

unosmecaDialog::unosmecaDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::unosmecaDialog)
{
    ui->setupUi(this);
}

unosmecaDialog::~unosmecaDialog()
{
    delete ui;
}

void unosmecaDialog::on_pushButton_2_clicked()
{
    this->reject();
}

void unosmecaDialog::on_pushButton_clicked()
{
    this->accept();
}

QString unosmecaDialog::getID()
{
    return this->ui->lineEdit->text();

}

QString unosmecaDialog::getIme()
{
    return this->ui->lineEdit_2->text();
}

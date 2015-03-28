/*
* (C) Copyright 2015
* Author: Nikola Knezevic <nkcodeplus@gmail.com>
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; version 2
* of the License.
*/

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

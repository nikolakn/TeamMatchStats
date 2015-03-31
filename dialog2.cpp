/*
* (C) Copyright 2015
* Authors:
* Nikola Knezevic <nkcodeplus@gmail.com>
* Goran Lapčević <gorlap@gmail.com>
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; version 2
* of the License.
*/

#include "dialog2.h"
#include "ui_dialog2.h"

Dialog2::Dialog2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog2)
{
    ui->setupUi(this);
    odabrano = 0;
    ui->comboBox->addItem("all games");
    ui->comboBox->addItem("Standard");
    ui->comboBox->addItem("960");
}

Dialog2::~Dialog2()
{
    delete ui;
}



void Dialog2::on_pushButton_clicked()
{
    QString ss=ui->comboBox->currentText();
    if(ss == "all games")
        odabrano= 0;
    if (ss == "Standard")
        odabrano = 1;
    if(ss == "960")
        odabrano = 2;
    this->accept();
}

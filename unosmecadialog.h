/*
* (C) Copyright 2015
* Author: Nikola Knezevic <nkcodeplus@gmail.com>
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; version 2
* of the License.
*/

#ifndef UNOSMECADIALOG_H
#define UNOSMECADIALOG_H

#include <QDialog>

namespace Ui {
class unosmecaDialog;
}

class unosmecaDialog : public QDialog
{
    Q_OBJECT

public:
    explicit unosmecaDialog(QWidget *parent = 0);
    ~unosmecaDialog();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();
public:
    QString getID();
    QString getIme();

private:
    Ui::unosmecaDialog *ui;
};

#endif // UNOSMECADIALOG_H

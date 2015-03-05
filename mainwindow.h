/*
* (C) Copyright 2015
* Author: Nikola Knezevic <nkcodeplus@gmail.com>
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; version 2
* of the License.
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include <QListView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QTableView>
#include <QLineEdit>
#include <QStandardItemModel>
#include <QPushButton>
#include "nkweb.h"
#include "nkmecevi.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void makeList();

public slots:
    void onOK_click();
    void stranicaSpremna();
private:
    Ui::MainWindow *ui;

    QLabel *adresaLabel;
    QLineEdit *adresa;
    QLabel *timLabel;
    QLineEdit *tim;
    QPushButton *dugme1;
    QListView *listview;
    QStandardItemModel *model;
    QStandardItem *Item;
    QTableView *resultView;
    NkWeb web;
    NkMecevi mecevi;
    int strana;
};

#endif // MAINWINDOW_H

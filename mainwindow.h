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
#include <QTableWidget>
#include <QLineEdit>
#include <QStandardItemModel>
#include <QPushButton>
#include "nkweb.h"
#include "nkmecevi.h"
#include "nkgames.h"
#include <QClipboard>
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
    void makeTable();

public slots:
    void onOK_click();
    void onCVS_click();
    void stranicaSpremna();
    void onUcitajTabelu();
    void onM1();
    void onM2();
    void onM3();
    void onM4();
    void onM5();
private:
    Ui::MainWindow *ui;

    QLabel *adresaLabel;
    QLineEdit *adresa;
    QLabel *timLabel;
    QLineEdit *tim;
    QPushButton *dugme1;
    QPushButton *dugme2;
    QListView *listview;
    QStandardItemModel *model;
    QStandardItem *Item;
    QTableWidget *resultView;
    QPushButton *m1;
    QPushButton *m2;
    QPushButton *m3;
    QPushButton *m4;
    QPushButton *m5;
    QPushButton *m6;
    QPushButton *m7;
    NkWeb web;
    NkMecevi mecevi;
    NkGames games;
    int strana;
    bool isGame;
    int kraj;
};

#endif // MAINWINDOW_H

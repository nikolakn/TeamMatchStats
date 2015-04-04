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
#include <QMenuBar>
#include <QComboBox>
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
    void prebrojcekirane();
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
    void onM8();
    void newFile();
    void open();
    void save();
    void saveXml();
    void klik();
    void nktableStat();
    void copynktableStat();
    void onAbout();
    void ReceiveChange(QStandardItem* i);
private:
    Ui::MainWindow *ui;
    QMenu *fileMenu;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveXmlAct;
    QMenu *toolMenu;
    QMenu *help;
    QAction *about;
    QAction *tablestat;
    QAction *copytablestat;
    QLabel *adresaLabel;
    QComboBox *adresa;
    QLabel *timLabel;
    QLineEdit *tim;
    QPushButton *dugme1;
    QPushButton *dugme2;
    QListView *listview;
    QStandardItemModel *model;
    QStandardItem *Item;
    QStandardItem *Item2;
    QTableWidget *resultView;
    QPushButton *m1;
    QPushButton *m2;
    QPushButton *m3;
    QPushButton *m4;
    QPushButton *m5;
    QPushButton *m6;
    QPushButton *m7;
    QPushButton *m8;
    NkWeb web;
    NkMecevi mecevi;
    NkGames games;
    int strana;
    bool isGame;
    int kraj;
    int odabrano;
    bool ucitavanje;
    bool zavrsene;
};

#endif // MAINWINDOW_H

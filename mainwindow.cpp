/*
* (C) Copyright 2015
* Author: Nikola Knezevic <nkcodeplus@gmail.com>
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; version 2
* of the License.
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QScrollArea>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    strana=1;
    isGame=false;
    kraj=0;
    adresaLabel = new QLabel(tr("Adresa:"));
    adresa = new QLineEdit();
    adresa->setText("http://www.chess.com/groups/team_match_archive?id=8083");

    timLabel = new QLabel(tr("Tim:"));
    tim = new QLineEdit();
    tim->setMaximumWidth(80);
    tim->setFixedWidth(100);

    tim->setText("Srbija Tim");
    dugme1 = new QPushButton(tr("Ucitaj Mečeve"));
    dugme2 = new QPushButton(tr("Copy CSV"));

    QHBoxLayout *adresaLayout = new QHBoxLayout;
    adresaLayout->addWidget(adresaLabel);
    adresaLayout->addWidget(adresa);
    adresaLayout->addWidget(timLabel);
    adresaLayout->addWidget(tim);
    adresaLayout->addWidget(dugme1);
    adresaLayout->addWidget(dugme2);

    QSplitter *splitter = new QSplitter(parent);
    QWidget *leftSide = new QWidget;


    listview = new QListView();
    QVBoxLayout *levo = new QVBoxLayout;
    m1 = new QPushButton(tr("Čekiraj Sve"));
    m2 = new QPushButton(tr("Nista"));
    m3 = new QPushButton(tr("Prvih x meceva"));
    m4 = new QPushButton(tr("Naziv sadrzi..."));
    m5 = new QPushButton(tr("Unesi rucno link od meča..."));
    m6 = new QPushButton(tr("Napravi tabelu>>>"));
    levo->addWidget(m1);
    levo->addWidget(m2);
    levo->addWidget(m3);
    levo->addWidget(m4);
    levo->addWidget(m5);
    levo->addWidget(m6);
    levo->addWidget(listview);
    leftSide->setLayout( levo );



    model = new QStandardItemModel();

    listview->setModel( model );

    resultView = new QTableWidget();
    resultView->setSortingEnabled(true);
    //resultView->setColumnCount(7);


    splitter->addWidget(leftSide);
    splitter->addWidget(resultView);



    QList<int> a={200,600};
    splitter->setSizes(a);

    QVBoxLayout *mainLayout = new QVBoxLayout(parent);
    mainLayout->addLayout(adresaLayout);
    mainLayout->addWidget(splitter);

    this->centralWidget()->setLayout(mainLayout);
    setWindowTitle(tr("Team Match Stats"));
    connect(dugme1, SIGNAL(clicked()), this, SLOT(onOK_click()));
    connect(dugme2, SIGNAL(clicked()), this, SLOT(onCVS_click()));
    connect(&web, SIGNAL(gotovo()), this, SLOT(stranicaSpremna()));

    connect(m6, SIGNAL(clicked()), this, SLOT(onUcitajTabelu()));
    connect(m1, SIGNAL(clicked()), this, SLOT(onM1()));
    connect(m2, SIGNAL(clicked()), this, SLOT(onM1()));
    connect(m3, SIGNAL(clicked()), this, SLOT(onM1()));
    connect(m4, SIGNAL(clicked()), this, SLOT(onM1()));
    connect(m5, SIGNAL(clicked()), this, SLOT(onM1()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::makeList()
{
    QList<QString> spisak=mecevi.getList();
    int i=0;
    for(QString s : spisak){
        Item = new QStandardItem();
        Item->setCheckable( true );
        Item->setText(s);
        Item->setCheckState( Qt::Checked );
        model->setItem( i++, Item );
    }
    QString str;
    str.setNum(spisak.size());
    setWindowTitle("Ukupno Meceva: "+str);

}

void MainWindow::makeTable()
{
    QList<QString> linkovi=mecevi.getLinks();
    int i=0;
    for(QString s : linkovi){
        i++;
        isGame=true;
        if(i==linkovi.size())
            kraj=1;

        web.getPage("http://www.chess.com"+s);

    }

}

void MainWindow::onOK_click()
{
    // games.print(resultView);
    model->clear();
    games.clear();
    mecevi.clear();
    kraj=0;
    isGame=false;
    strana=1;
    web.getPage(adresa->text()+"&page=1");
}

void MainWindow::onCVS_click()
{
    QClipboard *p_Clipboard = QApplication::clipboard();
    p_Clipboard->setText(games.copyToClip());
}

void MainWindow::stranicaSpremna()
{
    if(!isGame){
        //if page with team_match lists are loaded
        QString pp=web.get();

        if(mecevi.parsPage(pp,strana)){
            strana++;
            QString str;
            str.setNum(strana);
            isGame=false;
            setWindowTitle("Ucitavam Stranice: "+str);
            web.getPage(adresa->text()+"&page="+str);
            return;

        }
        else{
            makeList();
            return;
        }
    }
    else{
    //lodad page with games
        QString pp=web.get();

        if(games.parsPage(pp,tim->text())){
            if(kraj==1)
               games.print(resultView);
            return;
        }

    }

}

void MainWindow::onUcitajTabelu()
{
    makeTable();
}

void MainWindow::onM1()
{

}

void MainWindow::onM2()
{

}

void MainWindow::onM3()
{

}

void MainWindow::onM4()
{

}

void MainWindow::onM5()
{

}

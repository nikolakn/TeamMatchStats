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


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    strana=1;
    adresaLabel = new QLabel(tr("Adresa:"));
    adresa = new QLineEdit();
    adresa->setText("http://www.chess.com/groups/team_match_archive?id=8083");

    timLabel = new QLabel(tr("Tim:"));
    tim = new QLineEdit();
    tim->setMaximumWidth(80);
    tim->setFixedWidth(100);

    tim->setText("Srbija Tim");
    dugme1 = new QPushButton(tr("Ok"));

    QHBoxLayout *adresaLayout = new QHBoxLayout;
    adresaLayout->addWidget(adresaLabel);
    adresaLayout->addWidget(adresa);
    adresaLayout->addWidget(timLabel);
    adresaLayout->addWidget(tim);
    adresaLayout->addWidget(dugme1);

    QSplitter *splitter = new QSplitter(parent);

    listview = new QListView();
    model = new QStandardItemModel();

    listview->setModel( model );

    resultView = new QTableView();

    splitter->addWidget(listview);
    splitter->addWidget(resultView);
    QList<int> a={200,600};
    splitter->setSizes(a);

    QVBoxLayout *mainLayout = new QVBoxLayout(parent);
    mainLayout->addLayout(adresaLayout);
    mainLayout->addWidget(splitter);

    this->centralWidget()->setLayout(mainLayout);
    setWindowTitle(tr("Team Match Stats"));
    connect(dugme1, SIGNAL(clicked()), this, SLOT(onOK_click()));
    connect(&web, SIGNAL(gotovo()), this, SLOT(stranicaSpremna()));
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

void MainWindow::onOK_click()
{
    model->clear();
    mecevi.clear();
    strana=1;
    web.getPage(adresa->text()+"&page=1");
}

void MainWindow::stranicaSpremna()
{
    QString pp=web.get();

    QRegExp rx("<body>(.+)</body>");
    if (rx.indexIn(pp) != -1)
        pp = rx.cap(1);


    if(mecevi.parsPage(pp,strana)){
        strana++;
        QString str;
        str.setNum(strana);
        web.getPage(adresa->text()+"&page="+str);
        setWindowTitle("Ucitavam Stranice: "+str);
    }
    else{
        makeList();
        return;
    }
    return;

}

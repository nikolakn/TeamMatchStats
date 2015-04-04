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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QScrollArea>
#include <QInputDialog>
#include <QFileDialog>
#include "dialog2.h"
#include "unosmecadialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    strana=1;
    odabrano=0;
    isGame=false;
    kraj=0;
    adresaLabel = new QLabel(tr("Adresa:"));
    adresa = new QComboBox();
    adresa->addItem("http://www.chess.com/groups/team_match_archive?id=8083");
    adresa->addItem("http://www.chess.com/groups/matches/srbija-tim?show_all_current=1");
    adresa->setEditable(true);
    timLabel = new QLabel(tr("Tim:"));
    tim = new QComboBox();
    tim->addItem("Srbija Tim");
    tim->addItem("ISK Crvena Zvezda");
    tim->addItem("Serbia-Russia Team");
    tim->addItem("The Orthodox Christian Chess Players");
    tim->addItem("Svetozar Gligoric Chess Club");



    tim->setEditable(true);

    tim->setMaximumWidth(80);
    tim->setFixedWidth(200);

    dugme1 = new QPushButton(tr("Ucitaj Mečeve"));
    dugme2 = new QPushButton(tr("Kopiraj CSV"));

    QHBoxLayout *adresaLayout = new QHBoxLayout;
    adresaLayout->addWidget(adresaLabel);
    adresaLayout->addWidget(adresa,1);
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
    //m5 = new QPushButton(tr("Unesi rucno link od meča..."));
    m6 = new QPushButton(tr("Napravi tabelu>>>"));

    m8 = new QPushButton(tr("Poslednjih x meceva"));
    levo->addWidget(m1);
    levo->addWidget(m2);
    levo->addWidget(m3);
    levo->addWidget(m8);
    levo->addWidget(m4);
    //levo->addWidget(m5);
    levo->addWidget(m6);
    levo->addWidget(listview);
    leftSide->setLayout( levo );

    model = new QStandardItemModel(0,2,this);

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

    newAct = new QAction(tr("&Novi"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Novi"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    openAct = new QAction(tr("&Otvori listu"), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("otvori sacuvanu listu"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));


    saveAct = new QAction(tr("&Sacuvaj listu"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("snimi listu"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));


    saveXmlAct = new QAction(tr("&Sacuvaj Tebelu u Excel xml"), this);
    saveXmlAct->setStatusTip(tr("snimi tabelu"));
    connect(saveXmlAct, SIGNAL(triggered()), this, SLOT(saveXml()));

    tablestat = new QAction(tr("&Timska statistika"), this);
    tablestat->setStatusTip(tr("Timska statistika"));
    connect(tablestat, SIGNAL(triggered()), this, SLOT(nktableStat()));

    copytablestat = new QAction(tr("&Copy Timska statistika"), this);
    copytablestat->setStatusTip(tr("Copy Timska statistika"));
    connect(copytablestat, SIGNAL(triggered()), this, SLOT(copynktableStat()));

    connect(tim,SIGNAL(currentIndexChanged(const QString&)),
            this,SLOT(timPromenjen(const QString&)));

    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveXmlAct);
    fileMenu->addAction(saveAct);
    fileMenu->addSeparator();

    toolMenu = menuBar()->addMenu(tr("&Tools"));
    toolMenu->addAction(tablestat);
    toolMenu->addAction(copytablestat);


    about = new QAction(tr("&O Programu"), this);
    connect(about, SIGNAL(triggered()), this, SLOT(onAbout()));
    help = menuBar()->addMenu(tr("&Help"));
    help->addAction(about);


    connect(dugme1, SIGNAL(clicked()), this, SLOT(onOK_click()));
    connect(dugme2, SIGNAL(clicked()), this, SLOT(onCVS_click()));
    connect(&web, SIGNAL(gotovo()), this, SLOT(stranicaSpremna()));
    connect(m6, SIGNAL(clicked()), this, SLOT(onUcitajTabelu()));
    connect(m1, SIGNAL(clicked()), this, SLOT(onM1()));
    connect(m2, SIGNAL(clicked()), this, SLOT(onM2()));
    connect(m3, SIGNAL(clicked()), this, SLOT(onM3()));
    connect(m8, SIGNAL(clicked()), this, SLOT(onM8()));
    connect(m4, SIGNAL(clicked()), this, SLOT(onM4()));
    //connect(m5, SIGNAL(clicked()), this, SLOT(onM5()));
    connect(model,SIGNAL(itemChanged(QStandardItem*)), this, SLOT(ReceiveChange(QStandardItem*)));
    ucitavanje=true;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::makeList()
{
    ucitavanje=true;
    int i=0;
    QVector<Mec> mm= mecevi.getMecevi();
    for(Mec s : mm){
        Item = new QStandardItem();
        Item->setCheckable( true );
        QString a2=("("+s.rez+")");
        Item->setText(s.tabli+" "+a2+"   "+s.timovi);

        if(s.selekted)
            Item->setCheckState( Qt::Checked );
        else
            Item->setCheckState( Qt::Unchecked );
        //zavrsena partija
        if(s.procenat=="Won"){
            QBrush bb(QColor(20,150,20));
            Item->setForeground(bb);
        }
        if(s.procenat=="Lost"){
            QBrush bb(QColor(150,0,0));
            Item->setForeground(bb);
        }
        int rez=-1;
        QStringList list= s.rez.split(QRegExp("[|]"),QString::SkipEmptyParts);
        if(list.size()==2){
            QString tabli=s.tabli.trimmed();
            QString r1=list[0].trimmed();
            QString r2=list[1].trimmed();
            double dr1=r1.toDouble();
            double dr2=r2.toDouble();
            double tab=tabli.toDouble();

            if(dr1>tab)
                rez=1;
            if(dr2>tab)
                rez=2;
            //qDebug() << r1 << " " << r2;
        }
        QBrush bb2(QColor(220,220,220));
        // partija u toku
        if(s.pobeda=="Winning"){
            if(rez==1){
                QBrush bb(QColor(20,150,20));
                Item->setForeground(bb);
                Item->setBackground(bb2);
            } else{
                QBrush bb(QColor(0,0,200));
                Item->setForeground(bb);
                Item->setBackground(bb2);
            }
        }
        if(s.pobeda=="Losing"){
            if(rez==2){
                QBrush bb(QColor(150,0,0));
                Item->setForeground(bb);
                Item->setBackground(bb2);
            } else {
                QBrush bb(QColor(250,100,100));
                Item->setForeground(bb);
                Item->setBackground(bb2);
            }
        }
        if(s.pobeda=="Tied"){
            QBrush bb(QColor(0,0,0));
            Item->setForeground(bb);
            Item->setBackground(bb2);
        }
        model->setItem( i++,0, Item );
    }
    QString str;
    str.setNum(mm.size());
    //setWindowTitle("Ukupno Meceva: "+str);
    ucitavanje=false;
    prebrojcekirane();
}

void MainWindow::makeTable()
{
    games.clear();
    resultView->clear();
    mecevi.unCheckAll();
    // qDebug() << mecevi.getSelected();
    for(int i=0;i< model->rowCount();i++){
        if(model->item(i)->checkState()==Qt::Checked ){
            mecevi.Check(i);
        }
    }
    QList<QString> linkovi=mecevi.getLinks();
    int rez=mecevi.getSelected();
    //qDebug()<<linkovi.size()<<" aaaa "<<rez;
    int i=0;
    int dodato=0;
    for(QString s : linkovi){
        if(model->item(i)->checkState()==Qt::Checked ){

            dodato++;
            isGame=true;
            //qDebug()<< dodato<<" !!! "<<rez;
            if(dodato==rez)
                kraj=1;
            web.getPage("http://www.chess.com"+s);
        }
        i++;
    }
}

void MainWindow::prebrojcekirane()
{
    int brojcekiranih=0;
    for(int i=0;i< model->rowCount();i++){
        if(model->item(i)->checkState()==Qt::Checked ){
            brojcekiranih++;
        }
    }
    QString str="";
    QString str1="";
    setWindowTitle("Tim: ("+ tim->currentText()+") Ukupan broj mečeva u bazi: ("+str1.setNum(model->rowCount()) +") Broj odabranih mečeva: ("+str.setNum(brojcekiranih)+")");
}

void MainWindow::onOK_click()
{
    // games.print(resultView);
    resultView->clear();
    //model->clear();
    games.clear();
    //mecevi.clear();
    kraj=0;
    isGame=false;
    strana=1;
    if(adresa->currentText().left(36)=="http://www.chess.com/groups/matches/"){
        zavrsene=false;
        web.getPage(adresa->currentText());
    }else{
        zavrsene=true;
        web.getPage(adresa->currentText()+"&page=1");
    }
}

void MainWindow::onCVS_click()
{
    QClipboard *p_Clipboard = QApplication::clipboard();
    p_Clipboard->setText(games.copyToClip());
    //p_Clipboard->setText(games.toExcelXML());
}

void MainWindow::stranicaSpremna()
{
    if(!isGame){
        if(zavrsene){
            //if page with team_match lists are loaded
            QString pp=web.get();

            if(mecevi.parsPage(pp,strana)){
                strana++;
                QString str;
                str.setNum(strana);
                isGame=false;
                setWindowTitle("Ucitavam Stranice: "+str);
                web.getPage(adresa->currentText()+"&page="+str);
                return;
            }
            else{
                makeList();
                return;
            }
        } else{
            //qDebug() <<"utoku";
            //if page with team_match lists are loaded
            QString pp=web.get();
            mecevi.parsPageUtoku(pp);
            makeList();
            return;
        }
    }
    else{
        //lodad page with games
        QString pp=web.get();

        if(games.parsPage(pp,tim->currentText(),odabrano)){
            if(kraj==1)
                games.print(resultView);
            return;
        }
    }
}

void MainWindow::onUcitajTabelu()
{
    Dialog2 d(this);
    int rez =d.exec();
    if(rez== QDialog::Accepted){
        odabrano = d.getOdabrano();
        makeTable();
    }
}

void MainWindow::onM1()
{
    for(int i=0;i< model->rowCount();i++){
        model->item(i)-> setCheckState( Qt::Checked );
        mecevi.Check(i);
    }
    prebrojcekirane();
}

void MainWindow::onM2()
{
    for(int i=0;i< model->rowCount();i++){
        model->item(i)-> setCheckState( Qt::Unchecked );
        mecevi.UnCheck(i);
    }
    prebrojcekirane();
}

void MainWindow::onM3()
{
    int r = QInputDialog::getInt(this,"Input","Prvih:",model->rowCount(),0,
                                 model->rowCount());
    onM2();
    if(model->rowCount()<r)
        r=model->rowCount();
    for(int i=0;i< r;i++){
        model->item(i)-> setCheckState( Qt::Checked );
        mecevi.Check(i);
    }
    prebrojcekirane();
}

void MainWindow::onM4()
{
    QString text = QInputDialog::getText(this, tr("Input"),
                                         tr("Naziv sadrzi:"), QLineEdit::Normal);
    if(text=="" || text==" ")
        return;
    onM2();
    text = text.toLower();
    for(int i=0;i< model->rowCount();i++){
        QString naz = model->item(i)->text();
        naz = naz.toLower();
        if(naz.contains(text)){
            model->item(i)-> setCheckState( Qt::Checked );
            mecevi.Check(i);
        }
    }
    prebrojcekirane();
}

void MainWindow::onM5()
{
    //QString link = QInputDialog::getText(this, tr("Input"),
    //                                     tr("Unesite Id meca (broj u linku od meca):"), QLineEdit::Normal);

    QString link="";
    QString ime="";
    unosmecaDialog dd;
    int aa = dd.exec();
    if(aa == QDialog::Accepted) {
        link = dd.getID();
        ime=dd.getIme();
    } else{
        return;
    }
    if(link=="" || link==" ")
        return;
    Item = new QStandardItem();
    Item->setCheckable( true );
    Item->setText(ime);
    Item->setCheckState( Qt::Checked );
    model->appendRow(Item );
    mecevi.addLink(link,ime);
    prebrojcekirane();
}

void MainWindow::onM8()
{
    int r = QInputDialog::getInt(this,"Input","Poslednjih:",model->rowCount(),0,
                                 model->rowCount());
    onM2();
    if(model->rowCount()<r)
        r=model->rowCount();
    int start=model->rowCount()-r;
    for(int i=start;i< model->rowCount();i++){
        model->item(i)-> setCheckState( Qt::Checked );
        mecevi.Check(i);
    }
    prebrojcekirane();
}

void MainWindow::newFile()
{
    resultView->clear();
    model->clear();
    games.clear();
    mecevi.clear();
    kraj=0;
    isGame=false;
    strana=1;
    prebrojcekirane();
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Otvori listu meceva"), "",
                                                    tr("Lista meceva (*.mec);;All Files (*)"));
    if (fileName.isEmpty())
        return;
    else {

        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Ne mogu da otvorim fajl"),
                                     file.errorString());
            return;
        }

        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_4_5);
        newFile();
        mecevi.open(in);
        makeList();
    }
    //in >> contacts;
}

void MainWindow::save()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Sacuvaj listu meceva"), "",
                                                    tr("Lista meceva (*.mec);;All Files (*)"));
    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Nemogu da otvorim fajl"),file.errorString());
            return;
        }
        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_4_5);
        mecevi.save(out);
    }

}

void MainWindow::saveXml()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Sacuvaj tabeli"), "",
                                                    tr("Lista meceva (*.xml);;All Files (*)"));
    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::information(this, tr("Nemogu da otvorim fajl"),file.errorString());
            return;
        }
        QTextStream outStream(&file);
        outStream << games.toExcelXML();
    }
}

void MainWindow::klik()
{

}

void MainWindow::nktableStat()
{
    QMessageBox box;
    box.setText(games.toolbar());
    box.exec();
}

void MainWindow::copynktableStat()
{
    QClipboard *p_Clipboard = QApplication::clipboard();
    p_Clipboard->setText(games.toolbar());

}

void MainWindow::onAbout()
{
    QMessageBox::about(this,"O programu"," (C) Copyright 2015 \n Nikola Knežević <nkcodeplus@gmail.com> \n Goran Lapčević <gorlap@gmail.com> \n\nThis program is free software; you can redistribute it and/or\n modify it under the terms of the GNU General Public License\nas published by the Free Software Foundation; version 2\nof the License." );

}

void MainWindow::ReceiveChange(QStandardItem *i)
{
    if(i->checkState()==Qt::Checked)
        mecevi.Check(i->index().row());
    else
        mecevi.UnCheck(i->index().row());
    prebrojcekirane();
}

void MainWindow::timPromenjen(const QString &)
{

    QString ss=tim->currentText();
    if(ss == "Srbija Tim"){
        adresa->clear();
        adresa->addItem("http://www.chess.com/groups/team_match_archive?id=8083");
        adresa->addItem("http://www.chess.com/groups/matches/srbija-tim?show_all_current=1");
    }
    if (ss == "ISK Crvena Zvezda"){
        adresa->clear();
        adresa->addItem("http://www.chess.com/groups/team_match_archive?id=11119");
        adresa->addItem("http://www.chess.com/groups/matches/isk-crvena-zvezda?show_all_current=1");
    }

    if (ss == "Serbia-Russia Team"){
        adresa->clear();
        adresa->addItem("http://www.chess.com/groups/team_match_archive?id=28458");
        adresa->addItem("http://www.chess.com/groups/matches/serbia-russia-team?show_all_current=1");
    }

    if (ss == "The Orthodox Christian Chess Players"){
        adresa->clear();
        adresa->addItem("http://www.chess.com/groups/team_match_archive?id=9938");
        adresa->addItem("http://www.chess.com/groups/matches/the-orthodox-christian-chess-players?show_all_current=1");
    }
    if (ss == "Svetozar Gligoric Chess Club"){
        adresa->clear();
        adresa->addItem("http://www.chess.com/groups/team_match_archive?id=12539");
        adresa->addItem("http://www.chess.com/groups/matches/svetozar-gligoric-chess-club?show_all_current=1");
    }

}


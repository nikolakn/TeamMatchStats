/*
* (C) Copyright 2015
* Author: Nikola Knezevic <nkcodeplus@gmail.com>
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; version 2
* of the License.
*/

#include "nkgames.h"
#include <QDebug>
#include <QStringList>
#include "TableItem.h"
#include "TableItemDouble.h"

NkGames::NkGames(QObject *parent) :
    QObject(parent)
{
}

bool NkGames::parsPage(QString html, QString Tim, int vrsta){
    //qDebug() <<"prolaz";
    QString temp=html;
    QRegExp rx("<table class=\"default border-top alternate\">(.+)</table>");
    if (rx.indexIn(html) != -1)
        html = rx.cap(1);
    //qDebug()<<html;
    html="<table>"+html+"</table>";
    QWebPage page;
    QWebFrame * frame = page.mainFrame();
    frame->setHtml(html);
    QWebElement parse = frame->documentElement();
    QString tabela=parse.toPlainText();

    QStringList list= tabela.split(QRegExp("[\r\n]"),QString::SkipEmptyParts);
    if(list.size()==0) return false;
    QString timovi=list.at(0);
    if(timovi.size()==0) return false;
    timovi=timovi.right(timovi.size()-1);
    timovi=timovi.trimmed();
    //boja
    bool beli = true;
    if(timovi.left(Tim.size()).toLower()==Tim.toLower())
        beli = true;
    else
        beli = false;

    list.removeFirst();
    list.removeLast();

    ///////////////////////////

    QRegExp rx2("<table class=\"simple border-top clearfix alternate\">(.+)</table>");
    if (rx2.indexIn(temp) != -1)
        temp = rx2.cap(1);
    //qDebug()<<html;
    temp="<table>"+temp+"</table>";
    QWebPage page2;
    QWebFrame * frame2 = page2.mainFrame();
    frame2->setHtml(temp);
    QWebElement parse2 = frame2->documentElement();
    QWebElement str = parse2.findFirst("tbody tr");

    //QWebElement tt =str.findFirst("tr");
    //qDebug() << str.toPlainText();
    QString info = str.toPlainText();
    bool tip = true;
    if(info.contains("Standard Chess"))
        tip = true;
    if(info.contains("Chess960"))
        tip = false;

    if(vrsta==1){
        if(!tip)
            return false;
    }
    if(vrsta==2){
        if(tip)
            return false;
    }

    ///////////////////////////



    for(QString ll : list){
        QStringList partija= ll.split(QRegExp("\\s+"));
        //qDebug()<<ll;
        bool ok;
        partija.at(0).toInt(&ok);
        if(ok==0){
            return false;
        }

        QString ime="";
        double bodovi=0;
        double bodoviProt=0;
        QString r1,r2;
        if(beli){
            ime=partija.at(1);
            bodovi = partija.at(3).toDouble();
            bodoviProt = partija.at(7).toDouble();
            r1=partija.at(2);
            r2=partija.at(9);
        }
        else{
            ime=partija.at(8);
            bodovi = partija.at(7).toDouble();
            bodoviProt = partija.at(3).toDouble();
            r1=partija.at(9);
            r2=partija.at(2);
        }

        bool nasao = false;

        for(players &x : igraci){
            if (x.Ime==ime){
                //////////
                x.brojOdigranih+=2;
                r2=r2.left(r2.size()-1);
                r2=r2.right(r2.size()-1);
                int rp = r2.toInt();
                if(vrsta == 0 && !tip){

                } else{
                if(rp > x.rejtingprotivnika)
                    x.rejtingprotivnika=(x.rejtingprotivnika+rp)/2;
                }

                r1=r1.left(r1.size()-1);
                r1=r1.right(r1.size()-1);
                int raiting=r1.toInt();
                if(vrsta == 0 && !tip){

                } else{
                if(raiting > x.rejting){
                        x.rejting=raiting;
                }
                }
                //dali je zavrsena
                if((bodovi+bodoviProt)== 2){
                    if(bodovi==0){
                        x.poraza+=2;
                    }
                    if(bodovi==0.5){
                        x.poraza+=1;
                        x.remija+=1;
                    }
                    if(bodovi==1){
                        x.poraza+=1;
                        x.pobeda+=1;
                    }
                    if(bodovi==1.5){
                        x.pobeda+=1;
                        x.remija+=1;
                    }
                    if(bodovi==2){
                        x.pobeda+=2;
                        x.remija+=0;
                    }
                }  else{
                    if(bodovi==0){
                        if(bodoviProt==1){
                            x.poraza+=1;
                        }
                    }
                    if(bodovi==0.5){
                        if(bodoviProt==0.5){
                            x.remija+=1;
                        }

                    }
                    if(bodovi==1){
                        if(bodoviProt==0){
                           x.pobeda+=1;
                        }
                    }

                }
                x.bodova+=bodovi;
                x.bilans = x.pobeda - x.poraza;

                x.doprinos=x.bilans*x.bodova;
                x.procenatPobeda=(x.bodova*100.0/x.brojOdigranih);
                ////////////
                nasao = true;
                goto petlja;
            }
        }

        petlja:

        if(nasao==false){

            players i;
            i.Ime=ime;
            r1=r1.left(r1.size()-1);
            r1=r1.right(r1.size()-1);
            i.rejting=r1.toInt();
            i.brojOdigranih=2;
            i.poraza=0;
            i.remija=0;
            i.pobeda=0;

            r2=r2.left(r2.size()-1);
            r2=r2.right(r2.size()-1);
            i.rejtingprotivnika=r2.toInt();

            i.bodova = bodovi;
            //dali je zavrsena
            if((bodovi+bodoviProt)== 2){
                if(bodovi==0){
                    i.poraza=2;
                    i.pobeda=0;
                    i.remija=0;
                }
                if(bodovi==0.5){
                    i.poraza=1;
                    i.pobeda=0;
                    i.remija=1;
                }
                if(bodovi==1){
                    i.poraza=1;
                    i.pobeda=1;
                    i.remija=0;
                }
                if(bodovi==1.5){
                    i.poraza=0;
                    i.pobeda=1;
                    i.remija=1;
                }
                if(bodovi==2){
                    i.poraza=0;
                    i.pobeda=2;
                    i.remija=0;
                }
            }  else{
                qDebug()<<"nezavrsena";
                if(bodovi==0){
                    if(bodoviProt==1){
                        i.poraza=1;
                    }
                }
                if(bodovi==0.5){
                    if(bodoviProt==0.5){
                        i.remija=1;
                    }

                }
                if(bodovi==1){
                    if(bodoviProt==0){
                       i.pobeda=1;
                    }
                }

            }

            i.bilans = i.pobeda - i.poraza;
            i.bodova=bodovi;
            i.doprinos=i.bilans*i.bodova;
            i.procenatPobeda=(i.bodova*100.0/i.brojOdigranih);

            igraci.push_back(i);
        }

    }
    //qDebug()<<"prolaz10";
    //qDebug() << "odradio";
    return true;
}

void NkGames::print(QTableWidget *resultView)
{
    resultView->clear();
    resultView->setSortingEnabled(false);
    resultView->setColumnCount(10);
    resultView->setRowCount(igraci.size());

    QTableWidgetItem *h1 = new QTableWidgetItem("Ime");
    QTableWidgetItem *h2 = new QTableWidgetItem("Odigrano");
    QTableWidgetItem *h3 = new QTableWidgetItem("bodovi");
    QTableWidgetItem *h4 = new QTableWidgetItem("pobede");
    QTableWidgetItem *h5 = new QTableWidgetItem("porazi");
    QTableWidgetItem *h6 = new QTableWidgetItem("remi");
    QTableWidgetItem *h7 = new QTableWidgetItem("bilans");
    QTableWidgetItem *h8 = new QTableWidgetItem("%");
    QTableWidgetItem *h9 = new QTableWidgetItem("pros.r. protivnika");
    QTableWidgetItem *h10 = new QTableWidgetItem("rejting");
    resultView->setHorizontalHeaderItem(0,h1);
    resultView->setHorizontalHeaderItem(1,h10);
    resultView->setHorizontalHeaderItem(2,h2);
    resultView->setHorizontalHeaderItem(3,h3);
    resultView->setHorizontalHeaderItem(4,h4);
    resultView->setHorizontalHeaderItem(5,h5);
    resultView->setHorizontalHeaderItem(6,h6);
    resultView->setHorizontalHeaderItem(7,h7);
    resultView->setHorizontalHeaderItem(8,h8);
    resultView->setHorizontalHeaderItem(9,h9);

    resultView->setColumnWidth(1,60);
    resultView->setColumnWidth(2,60);
    resultView->setColumnWidth(3,60);
    resultView->setColumnWidth(4,60);
    resultView->setColumnWidth(5,60);
    resultView->setColumnWidth(6,60);
    resultView->setColumnWidth(7,60);
    resultView->setColumnWidth(8,60);
    int row=0;
    for(players x : igraci){

             QTableWidgetItem *newItem1 = new QTableWidgetItem(x.Ime);
             resultView->setItem(row, 0, newItem1);

             TableItem *newItem2 = new TableItem(tr("%1").arg(x.brojOdigranih));
             resultView->setItem(row, 2, newItem2);

             TableItemDouble *newItem3 = new TableItemDouble(tr("%1").arg(x.bodova));
             resultView->setItem(row, 3, newItem3);

             TableItem *newItem4 = new TableItem(tr("%1").arg(x.pobeda));
             resultView->setItem(row, 4, newItem4);

             TableItem *newItem5 = new TableItem(tr("%1").arg(x.poraza));
             resultView->setItem(row, 5, newItem5);

             TableItem *newItem6 = new TableItem(tr("%1").arg(x.remija));
             resultView->setItem(row, 6, newItem6);

             TableItem *newItem8 = new TableItem(tr("%1").arg(x.bilans));
             resultView->setItem(row, 7, newItem8);

             //TableItem *newItem9 = new TableItem(tr("%1").arg(x.doprinos));
             //resultView->setItem(row, 8, newItem9);

             TableItem *newItem7 = new TableItem(tr("%1").arg(x.procenatPobeda));
             resultView->setItem(row, 8, newItem7);

             TableItem *newItem10 = new TableItem(tr("%1").arg(x.rejting));
             resultView->setItem(row, 1, newItem10);

             TableItem *newItem11 = new TableItem(tr("%1").arg(x.rejtingprotivnika));
             resultView->setItem(row, 9, newItem11);
             row++;
    }
    resultView->setSortingEnabled(true);
    resultView->sortByColumn(1);
}

void NkGames::clear(){
    igraci.clear();
}

QString NkGames::copyToClip()
{
    QString oo;
    QTextStream s(&oo);
    s << "Ime;"<<"Rejting;" <<"Odigrano;"<<"bodovi;"<<"pobede;"<<"porazi;"<<"remi;"<<"bilans;"<<"%;"<<"pro.r. protivnika"<<endl;

    for(players x : igraci){

        s << x.Ime << ";";
        s << x.rejting << ";";
        s << x.brojOdigranih<< ";";
        s << x.bodova<< ";";
        s << x.pobeda<< ";";
        s << x.poraza<< ";";
        s << x.remija<< ";";
        s << x.bilans<< ";";
        //s << x.doprinos<< ";";
        s << x.procenatPobeda<< ";";
        s << x.rejtingprotivnika << endl;
    }
    return s.readAll();
}

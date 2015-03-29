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
    nkbrojmeceva=0;
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
    nkbrojmeceva++;


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

                r1=r1.left(r1.size()-1);
                r1=r1.right(r1.size()-1);
                int raiting=r1.toInt();

                if(raiting > x.rejting){
                        x.rejting=raiting;
                }
                int trenutnozavrsenih=0;
                //dali je zavrsena
                if((bodovi+bodoviProt)== 2){
                    x.brojzavrsenih+=2;
                    trenutnozavrsenih=2;
                    if(bodovi==0){
                        x.poraza+=2;
                        x.izgubljenihmeceva+=1;
                    }
                    if(bodovi==0.5){
                        x.poraza+=1;
                        x.remija+=1;
                        x.izgubljenihmeceva+=1;
                    }
                    if(bodovi==1){
                        x.poraza+=1;
                        x.pobeda+=1;
                        x.neresenihmeceva+=1;
                    }
                    if(bodovi==1.5){
                        x.pobeda+=1;
                        x.remija+=1;
                        x.dobijenihmeceva+=1;
                    }
                    if(bodovi==2){
                        x.pobeda+=2;
                        x.dobijenihmeceva+=1;
                    }
                }  else{
                    if(bodovi==0){
                        if(bodoviProt==1){
                            x.poraza+=1;
                            x.brojzavrsenih+=1;
                            trenutnozavrsenih=1;
                        }
                    }
                    if(bodovi==0.5){
                        if(bodoviProt==0.5){
                            x.remija+=1;
                            x.brojzavrsenih+=1;
                            trenutnozavrsenih=1;
                        }

                    }
                    if(bodovi==1){
                        if(bodoviProt==0){
                           x.pobeda+=1;
                           x.brojzavrsenih+=1;
                           trenutnozavrsenih=1;
                        }
                    }
                    if(bodoviProt==1.5)
                        x.izgubljenihmeceva+=1;
                    if(bodovi==1.5)
                        x.dobijenihmeceva+=1;

                }

                r2=r2.left(r2.size()-1);
                r2=r2.right(r2.size()-1);
                int rp = r2.toInt();
                //rp=rp;
                if(rp!=0){
                    if(trenutnozavrsenih>0)
                        x.reitinziprotivnika.push_back(rp);
                }
                x.bodova+=bodovi;
                x.bilans = x.pobeda - x.poraza;


                x.doprinos=x.bilans*x.bodova;
                if(x.brojzavrsenih!=0 || x.bodova!=0){
                    x.procenatPobeda=(x.bodova*100.0/x.brojzavrsenih);
                } else{
                    x.procenatPobeda=0;
                }

                long rr2=0;
                for(int pp1 : x.reitinziprotivnika){
                    if(rr2==0)
                        rr2=pp1;
                    else
                        rr2+=pp1;
                }
                if(x.reitinziprotivnika.size()!=0){

                    rr2=(rr2/x.reitinziprotivnika.size());
                }
                else{
                    rr2=1200;
                }
                x.rejtingprotivnika=(int)rr2;
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
            i.brojzavrsenih=0;
            i.dobijenihmeceva=0;
            i.izgubljenihmeceva=0;
            i.neresenihmeceva=0;


            i.bodova = bodovi;
            //dali je zavrsena
            if((bodovi+bodoviProt)== 2){
                i.brojzavrsenih=2;
                if(bodovi==0){
                    i.poraza=2;
                    i.pobeda=0;
                    i.remija=0;
                    i.izgubljenihmeceva=1;
                }
                if(bodovi==0.5){
                    i.poraza=1;
                    i.pobeda=0;
                    i.remija=1;
                    i.izgubljenihmeceva=1;
                }
                if(bodovi==1){
                    i.poraza=1;
                    i.pobeda=1;
                    i.remija=0;
                    i.neresenihmeceva=1;
                }
                if(bodovi==1.5){
                    i.poraza=0;
                    i.pobeda=1;
                    i.remija=1;
                    i.dobijenihmeceva=1;
                }
                if(bodovi==2){
                    i.poraza=0;
                    i.pobeda=2;
                    i.remija=0;
                    i.dobijenihmeceva=1;
                }

            }  else{
                //qDebug()<<"nezavrsena";
                if(bodovi==0){
                    if(bodoviProt==1){
                        i.poraza=1;
                        i.brojzavrsenih=1;
                    }
                }
                if(bodovi==0.5){
                    if(bodoviProt==0.5){
                        i.remija=1;
                        i.brojzavrsenih=1;
                    }

                }
                if(bodovi==1){
                    if(bodoviProt==0){
                       i.pobeda=1;
                       i.brojzavrsenih=1;
                    }
                }
                if(bodoviProt==1.5)
                    i.izgubljenihmeceva=1;
                if(bodovi==1.5)
                    i.dobijenihmeceva=1;


            }
            r2=r2.left(r2.size()-1);
            r2=r2.right(r2.size()-1);
            int rp = r2.toInt();

            i.reitinziprotivnika.clear();
            i.rejtingprotivnika=rp;
            i.rejtingprotivnika=i.rejtingprotivnika;
            if(i.rejtingprotivnika!=0){
                if(i.brojzavrsenih>0)
                i.reitinziprotivnika.push_back(i.rejtingprotivnika);
            }

            i.bilans = i.pobeda - i.poraza;
            i.bodova=bodovi;
            i.doprinos=i.bilans*i.bodova;
            if(i.brojzavrsenih!=0 || i.bodova!=0){
                i.procenatPobeda=(i.bodova*100.0/i.brojzavrsenih);
            } else{
                i.procenatPobeda=0;
            }

            long rr=0;
            for(auto pp : i.reitinziprotivnika){
                if(rr==0)
                    rr=pp;
                else
                    rr+=pp;
            }
            if(i.reitinziprotivnika.size()!=0)
                rr=rr/i.reitinziprotivnika.size();
            else
                rr=1200;
            i.rejtingprotivnika=(int)rr;
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
    resultView->setColumnCount(17);
    resultView->setRowCount(igraci.size());

    QTableWidgetItem *h1 = new QTableWidgetItem("Ime");
    QTableWidgetItem *h2 = new QTableWidgetItem("Odigrano");
    QTableWidgetItem *h11 = new QTableWidgetItem("Mečeva");

    QTableWidgetItem *h22 = new QTableWidgetItem("zavrseno");
    QTableWidgetItem *h23 = new QTableWidgetItem("u toku");

    QTableWidgetItem *h3 = new QTableWidgetItem("bodovi");
    QTableWidgetItem *h4 = new QTableWidgetItem("pobede");
    QTableWidgetItem *h5 = new QTableWidgetItem("porazi");
    QTableWidgetItem *h6 = new QTableWidgetItem("remi");
    QTableWidgetItem *h7 = new QTableWidgetItem("bilans");
    QTableWidgetItem *h8 = new QTableWidgetItem("%");
    QTableWidgetItem *h9 = new QTableWidgetItem("pros.r. protivnika");
    QTableWidgetItem *h10 = new QTableWidgetItem("rejting");
    QTableWidgetItem *h12 = new QTableWidgetItem("Rp");

    QTableWidgetItem *h13 = new QTableWidgetItem("dobijenih meč.");
    QTableWidgetItem *h14 = new QTableWidgetItem("nerešenih meč.");
    QTableWidgetItem *h15 = new QTableWidgetItem("izgubljenih meč.");

    resultView->setHorizontalHeaderItem(0,h1);
    resultView->setHorizontalHeaderItem(1,h10);
    resultView->setHorizontalHeaderItem(2,h11);
    resultView->setHorizontalHeaderItem(6,h2);

    resultView->setHorizontalHeaderItem(3,h13);
    resultView->setHorizontalHeaderItem(4,h14);
    resultView->setHorizontalHeaderItem(5,h15);



    resultView->setHorizontalHeaderItem(7,h22);
    resultView->setHorizontalHeaderItem(8,h23);

    resultView->setHorizontalHeaderItem(9,h4);

    resultView->setHorizontalHeaderItem(10,h6);
    resultView->setHorizontalHeaderItem(11,h5);
    resultView->setHorizontalHeaderItem(12,h3);

    resultView->setHorizontalHeaderItem(13,h7);
    resultView->setHorizontalHeaderItem(14,h8);
    resultView->setHorizontalHeaderItem(15,h9);
    resultView->setHorizontalHeaderItem(16,h12);

    resultView->setColumnWidth(1,60);
    resultView->setColumnWidth(2,50);
    resultView->setColumnWidth(3,50);
    resultView->setColumnWidth(4,50);
    resultView->setColumnWidth(5,50);
    resultView->setColumnWidth(6,50);
    resultView->setColumnWidth(7,50);
    resultView->setColumnWidth(8,50);
    resultView->setColumnWidth(9,50);
    resultView->setColumnWidth(10,50);
    resultView->setColumnWidth(11,50);
    resultView->setColumnWidth(12,50);
    resultView->setColumnWidth(13,50);
    resultView->setColumnWidth(14,50);
    resultView->setColumnWidth(15,50);
    resultView->setColumnWidth(16,50);
    int row=0;
    QColor c1(91,223,131);
    QColor c2(240,77,77);
    QColor c3(183,113,132);
    QColor c4(77,77,240);
    QColor c5(177,177,177);
    for(players x : igraci){
        int rp=1200;
        if(x.brojzavrsenih !=0){
             rp = x.rejtingprotivnika + (400 * x.bilans / x.brojzavrsenih);
        }
        if(rp<0)
            rp=1200;
             QTableWidgetItem *newItem1 = new QTableWidgetItem(x.Ime);
             resultView->setItem(row, 0, newItem1);

             TableItem *newItem111 = new TableItem(tr("%1").arg(x.brojOdigranih/2));
             resultView->setItem(row, 2, newItem111);

             TableItem *newItem2 = new TableItem(tr("%1").arg(x.brojOdigranih));
             newItem2->setBackgroundColor(c4);
             resultView->setItem(row, 6, newItem2);



             ///////
             TableItem *newItemM1 = new TableItem(tr("%1").arg(x.dobijenihmeceva));
             newItemM1->setBackgroundColor(c5);
             resultView->setItem(row, 3, newItemM1);

             TableItem *newItemM2 = new TableItem(tr("%1").arg(x.neresenihmeceva));
             newItemM2->setBackgroundColor(c5);
             resultView->setItem(row, 4, newItemM2);

             TableItem *newItemM3 = new TableItem(tr("%1").arg(x.izgubljenihmeceva));
             newItemM3->setBackgroundColor(c5);
             resultView->setItem(row, 5, newItemM3);
             ////////////////
             /// \brief newItem22
             ///
             TableItem *newItem22 = new TableItem(tr("%1").arg(x.brojzavrsenih));
             newItem22->setBackgroundColor(c4);
             resultView->setItem(row, 7, newItem22);

             TableItem *newItem23 = new TableItem(tr("%1").arg(x.brojOdigranih-x.brojzavrsenih));
             newItem23->setBackgroundColor(c4);
             resultView->setItem(row, 8, newItem23);


             TableItemDouble *newItem3 = new TableItemDouble(tr("%1").arg(x.bodova));
             newItem3->setBackgroundColor(c2);
             resultView->setItem(row, 12, newItem3);

             TableItem *newItem4 = new TableItem(tr("%1").arg(x.pobeda));
             newItem4->setBackgroundColor(c1);
             resultView->setItem(row, 9, newItem4);

             TableItem *newItem5 = new TableItem(tr("%1").arg(x.poraza));
             newItem5->setBackgroundColor(c1);
             resultView->setItem(row, 10, newItem5);

             TableItem *newItem6 = new TableItem(tr("%1").arg(x.remija));
             newItem6->setBackgroundColor(c1);
             resultView->setItem(row, 11, newItem6);

             TableItem *newItem8 = new TableItem(tr("%1").arg(x.bilans));
             newItem8->setBackgroundColor(c2);
             resultView->setItem(row, 13, newItem8);

             //TableItem *newItem9 = new TableItem(tr("%1").arg(x.doprinos));
             //resultView->setItem(row, 8, newItem9);

             TableItem *newItem7 = new TableItem(tr("%1").arg(x.procenatPobeda));
             newItem7->setBackgroundColor(c2);
             resultView->setItem(row, 14, newItem7);

             TableItem *newItem10 = new TableItem(tr("%1").arg(x.rejting));
             resultView->setItem(row, 1, newItem10);

             TableItem *newItem11 = new TableItem(tr("%1").arg(x.rejtingprotivnika));
             newItem11->setBackgroundColor(c3);
             resultView->setItem(row, 15, newItem11);

             TableItem *newItem12= new TableItem(tr("%1").arg(rp));
             newItem12->setBackgroundColor(c3);
             resultView->setItem(row, 16, newItem12);
             row++;
    }
    resultView->setSortingEnabled(true);
    resultView->sortByColumn(1);

}

void NkGames::clear(){
    igraci.clear();
    nkbrojmeceva=0;
}

QString NkGames::copyToClip()
{
    QString oo;
    QTextStream s(&oo);
    s << "Ime;"<<"Rejting;" <<"Mečeva;"<<"Dobijenih mečeva;"<<"Nerešenih mečeva;"<<"izgubljenih mečeva;"<<"Odigrano;"<<"Zavrseno;"<<"U toku;"<<"pobede;"<<"remi;"<<"porazi;"<<"bodovi;"<<"bilans;"<<"%;"<<"pro.r. protivnika;"<<"Rp"<<endl;

    for(players x : igraci){
        int rp=1200;
        if(x.brojzavrsenih !=0){
             rp = x.rejtingprotivnika + (400 * x.bilans / x.brojzavrsenih);
        }
        if(rp<0)
            rp=1200;
        s << x.Ime << ";";
        s << x.rejting << ";";
        s << x.brojOdigranih/2<< ";";
        s << x.dobijenihmeceva<< ";";
        s << x.neresenihmeceva<< ";";
        s << x.izgubljenihmeceva<< ";";
        s << x.brojOdigranih<< ";";
        s << x.brojzavrsenih<< ";";
        s << (x.brojOdigranih-x.brojzavrsenih)<< ";";   
        s << x.pobeda<< ";";
        s << x.remija<< ";";
        s << x.poraza<< ";";
        s << x.bodova<< ";";
        s << x.bilans<< ";";
        //s << x.doprinos<< ";";
        s << x.procenatPobeda<< ";";
        s << x.rejtingprotivnika << ";";
        s << rp << endl;
    }
    return s.readAll();
}

QString NkGames::toolbar()
{
    QString oo;
    QTextStream s(&oo);
    int odigranih=0;
    int utoku=0;
    int zavrsene=0;
    long raiting=0;
    long protivnik=0;
    int pobeda=0;
    int poraza=0;
    int remija=0;
    for(players x : igraci){
        odigranih+=x.brojOdigranih;
        zavrsene+=x.brojzavrsenih;
        if(raiting==0)
            raiting=x.rejting;
        else{
            if(x.rejting!=0)
            raiting+=x.rejting;

        }
        if(protivnik==0)

            protivnik=x.rejtingprotivnika;
        else{
            if(x.rejtingprotivnika!=0)
                protivnik+=x.rejtingprotivnika;
        }
        pobeda+=x.pobeda;
        poraza+=x.poraza;
        remija+=x.remija;

    }
    if(igraci.size()!=0){
        raiting = raiting/igraci.size();
        protivnik = protivnik/igraci.size();
        s << "Broj Meceva: " << nkbrojmeceva << endl;
        s << "ukupno igraca: " << igraci.size() << endl;
        s << "ukupno partija: " << odigranih << endl;
        s << "ukupno zavrsenih: " << zavrsene << endl;
        s << "trenutno se igra: " << odigranih-zavrsene << endl;
        s << "Broj pobeda: " << pobeda << endl;
        s << "Broj poraza: " << poraza << endl;
        s << "Broj remija: " << remija << endl;
        s << "Prosecan rejting: " << raiting << endl;
        s << "Prosecan rejting protivnika: " << protivnik << endl;
    }
    return s.readAll();
}

#include "nkgames.h"
#include <QDebug>
#include <QStringList>
#include "TableItem.h"
#include "TableItemDouble.h"
NkGames::NkGames(QObject *parent) :
    QObject(parent)
{
}

bool NkGames::parsPage(QString html, QString Tim){
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
        if(beli){
            ime=partija.at(1);
            bodovi = partija.at(3).toDouble();
            bodoviProt = partija.at(7).toDouble();
        }
        else{
            ime=partija.at(8);
            bodovi = partija.at(7).toDouble();
            bodoviProt = partija.at(3).toDouble();
        }
        bool nasao = false;

        for(players &x : igraci){
            if (x.Ime==ime){
                //////////
                x.bodova+=bodovi;
                x.brojOdigranih+=2;

                if(bodovi==0){
                    x.poraza+=2;
                }
                if(bodovi==0.5){
                    x.remija+=2;
                }
                if(bodovi==1){
                    x.poraza+=1;
                    x.pobeda+=1;
                }
                if(bodovi==1.5){
                    x.remija+=1;
                    x.pobeda+=1;
                }
                if(bodovi==2){
                    x.pobeda+=2;
                }
                x.procenatPobeda=((double)x.pobeda/x.brojOdigranih);
                ////////////
                nasao = true;
                goto petlja;
            }
        }

        petlja:

        if(nasao==false){

            players i;
            i.Ime=ime;
            i.bodova=bodovi;
            i.brojOdigranih=2;
            i.poraza=0;
            i.remija=0;
            i.pobeda=0;
            if(bodovi==0){
                i.poraza=2;
            }
            if(bodovi==0.5){
                //i.poraza=1;
                i.remija=2;
            }
            if(bodovi==1){
                i.poraza=1;
                i.pobeda=1;
            }
            if(bodovi==1.5){
                i.remija=1;
                i.pobeda=1;
            }
            if(bodovi==2){
                i.pobeda=2;
            }
            i.procenatPobeda=((double)i.pobeda/i.brojOdigranih);

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
    resultView->setSortingEnabled(true);
    resultView->setColumnCount(7);
    resultView->setRowCount(igraci.size());
    int row=0;
    for(players x : igraci){

             QTableWidgetItem *newItem1 = new QTableWidgetItem(x.Ime);
             resultView->setItem(row, 0, newItem1);

             TableItem *newItem2 = new TableItem(tr("%1").arg(x.brojOdigranih));
             resultView->setItem(row, 1, newItem2);

             TableItem *newItem3 = new TableItem(tr("%1").arg(x.bodova));
             resultView->setItem(row, 2, newItem3);

             TableItem *newItem4 = new TableItem(tr("%1").arg(x.pobeda));
             resultView->setItem(row, 3, newItem4);

             TableItem *newItem5 = new TableItem(tr("%1").arg(x.poraza));
             resultView->setItem(row, 4, newItem5);

             TableItem *newItem6 = new TableItem(tr("%1").arg(x.remija));
             resultView->setItem(row, 5, newItem6);

             TableItemDouble *newItem7 = new TableItemDouble(tr("%1").arg(x.procenatPobeda));
             resultView->setItem(row, 6, newItem7);

             row++;
    }
}

void NkGames::clear(){
    igraci.clear();
}

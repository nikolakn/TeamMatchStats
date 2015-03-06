#include "nkgames.h"
#include <QDebug>
#include <QStringList>

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
    QString timovi=list.at(0);
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

    for(QString x : list){

        QStringList partija= x.split(QRegExp("\\s+"));
        QString ime;
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
        for(players x : igraci){
            if (x.Ime==ime){
                //////////
                x.bodova+=bodovi;
                x.brojOdigranih+=2;

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
                    x.remija+=1;
                    x.pobeda+=1;
                }
                if(bodovi==2){
                    x.pobeda+=2;
                }
                x.procenatPobeda=((double)x.pobeda/x.brojOdigranih);
                ////////////
                nasao = true;
                break;
            }
        }
        if(!nasao){
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
                i.poraza=1;
                i.remija=1;
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


    return true;
}

void NkGames::print()
{
    for(players x : igraci){
        qDebug()<< x.Ime << x.brojOdigranih << x.bodova << x.pobeda << x.poraza << x.remija << x.procenatPobeda;
    }
}

void NkGames::clear(){

}

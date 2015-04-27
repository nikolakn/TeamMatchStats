#include "nkgamest.h"

#include "nkgamest.h"
#include <QDebug>
#include <QStringList>
#include "TableItem.h"
#include "TableItemDouble.h"
#include "cmath"

int NkGamesT::broj2 = 0;
NkGamesT::NkGamesT(QObject *parent) :
    QObject(parent)
{
    nkbrojmeceva=0;
}

bool NkGamesT::parsPage(QString html, QString Tim, int vrsta){
    //mlinkovi.clear();
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
    //QString tabela=parse.toPlainText();
    //////////////////////////////////////
    QString tabela=parse.toPlainText();
    int ind=tabela.indexOf(QRegExp("Comments"));
    tabela=tabela.left(ind);
    //qDebug() <<tabela;
    QStringList list= tabela.split(QRegExp("[\r\n]"),QString::SkipEmptyParts);
    if(list.size()==0) return false;
    QString timovi=list.at(0);
    if(timovi.size()==0) return false;
    timovi=timovi.right(timovi.size()-1);
    timovi=timovi.trimmed();
    //boja
    bool strana = true;
    if(timovi.left(Tim.size()).toLower()==Tim.toLower())
        strana = true;
    else
        strana = false;
    ////////////////////////
    QWebElementCollection str = parse.findAll("tbody tr");

    for(QWebElement el : str){
        //qDebug() << el.toPlainText();
        ///////////////////////////////
        QStringList partija= el.toPlainText().split(QRegExp("\\s+"));
        QString ime="";
        if(strana)
            ime=partija.at(1);
        else
            ime=partija.at(8);
        //////////////////////////////////
        QWebElementCollection linkovi = el.findAll("a");
         int brl = 0;
         int partijar = 0;
         for(QWebElement li : linkovi){
             QString ss = li.attribute("href");

             if(ss.left(8)=="/echess/") {
                NkLink nkl;
                nkl.link = "http://www.chess.com"+ss;
                nkl.ime = ime;
                if(strana && partijar==0)
                    nkl.beli = true;
                if(strana && partijar==1)
                    nkl.beli = false;

                if(!strana && partijar==0)
                    nkl.beli = false;
                if(!strana && partijar==1)
                    nkl.beli = true;

                mlinkovi.push_back(nkl);
                NkGamesT::broj2++;
                brl++;
                partijar++;
                //qDebug() << ss;
             }
         }
         //if(brl!=2)
             //qDebug() << brl;
    }
    //qDebug() << NkGamesT::broj2;

    return true;
}
void NkGamesT::clear(){
    mlinkovi.clear();
    nkbrojmeceva=0;
}
QList<NkLink> NkGamesT::getLinks(){
    return mlinkovi;
}

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

    QWebElementCollection str = parse.findAll("tbody tr");
    for(QWebElement el : str){
        NkGamesT::broj2 ++;
        qDebug() <<el.toPlainText();
    }
    qDebug() << NkGamesT::broj2;


    return true;
}
void NkGamesT::clear(){
    igraci.clear();
    nkbrojmeceva=0;
}

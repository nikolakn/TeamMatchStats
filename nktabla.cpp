#include "nktabla.h"
#include <qdebug.h>


NkTabla::NkTabla(QObject *parent) :
    QObject(parent)
{
    nkbrojmeceva=0;
}

bool NkTabla::parsPage(QString html, QString Tim,int igrac){

    if(igrac){
    QRegExp rx("<div class=\"plyrb\" id=\"bottomplayerdiv\">(.+)<h2 class=\"section-title top-32\">");
    if (rx.indexIn(html) != -1)
        html = rx.cap(1);

    html="<div><div><div>"+html;
    } else {
        QRegExp rx("<div class=\"plyrb\" id=\"topplayerdiv\">(.+)<div class=\"brd\">");
        if (rx.indexIn(html) != -1)
            html = rx.cap(1);

        html="<div>"+html;
    }
/*
    qDebug()<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
    qDebug()<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
    qDebug()<<html;
    qDebug()<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
    qDebug()<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
    //qDebug() << html;
*/
    QWebPage page;
    QWebFrame * frame = page.mainFrame();
    frame->setHtml(html);
    QWebElement parse = frame->documentElement();
    //QWebElement str = parse.findFirst("div.topplayerdiv");

    QString tabela=parse.toPlainText();

    rez = tabela;
    //qDebug() << tabela;
        ///////////////////////////////
        //QStringList partija= el.toPlainText().split(QRegExp("\\s+"));


    return true;
}
void NkTabla::clear(){

}

QString NkTabla::getRez()
{
    return rez;
}

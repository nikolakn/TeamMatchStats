#include "nktabla.h"
#include <qdebug.h>


NkTabla::NkTabla(QObject *parent) :
    QObject(parent)
{
    nkbrojmeceva=0;
}

bool NkTabla::parsPage(QString html, QString Tim, int igrac){

    if(igrac){
        QRegExp rx("<div class=\"plyrb\" id=\"topplayerdiv\">(.+)</div></div></div><div");
        if (rx.indexIn(html) != -1)
            html = rx.cap(1);
        else
            return false;
        //qDebug()<<html;
        html="<div>"+html+"</div>";
    } else{
        QRegExp rx("<div class=\"plyrb\" id=\"bottomplayerdiv\">(.+)</div></div></div><div");
        if (rx.indexIn(html) != -1)
            html = rx.cap(1);
        else
            return false;
        //qDebug()<<html;
        html="<div>"+html+"</div>";
    }
    //qDebug() << html;

    QWebPage page;
    QWebFrame * frame = page.mainFrame();
    frame->setHtml(html);
    QWebElement parse = frame->documentElement();

    QString tabela=parse.toPlainText();

    rez = tabela;
    qDebug() << tabela;
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

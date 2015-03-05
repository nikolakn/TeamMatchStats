#include "nkmecevi.h"
#include <QDebug>
NkMecevi::NkMecevi(QObject *parent) :
    QObject(parent)
{
}

void NkMecevi::parsPage(QString html)
{

    QRegExp rx("<body>(.+)</body>");
    if (rx.indexIn(html) != -1)
        html = rx.cap(1);

    QWebPage page;
    QWebFrame * frame = page.mainFrame();
    frame->setHtml(html);
    QWebElement parse = frame->documentElement();

    //QWebElement result = parse.firstChild();
    QWebElement result = parse.findFirst("table.alternate tbody");
    QWebElementCollection result2 = result.findAll("tr");
    for(QWebElement x : result2){
        //QWebElementCollection result2 = result.findAll("td");
        QWebElement link = x.findFirst("a");
         qDebug() << link.toPlainText() << link.attribute("href");
    }
    //int numTables = result2.count();
    //qDebug() << numTables;
}

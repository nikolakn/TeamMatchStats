#include "nkmecevi.h"
#include <QDebug>
NkMecevi::NkMecevi(QObject *parent) :
    QObject(parent)
{
}

bool NkMecevi::parsPage(QString html, int st)
{

    QRegExp rx("<body>(.+)</body>");
    if (rx.indexIn(html) != -1)
        html = rx.cap(1);

    QWebPage page;
    QWebFrame * frame = page.mainFrame();
    frame->setHtml(html);
    QWebElement parse = frame->documentElement();
    //page num
    QWebElement str = parse.findFirst("ul.pagination li.current");

    if(str.toPlainText().toInt()!=st)
        return false;
    //QWebElement result = parse.firstChild();
    QWebElement result = parse.findFirst("table.alternate tbody");
    QWebElementCollection result2 = result.findAll("tr");
    for(QWebElement x : result2){
        //QWebElementCollection result2 = result.findAll("td");
        QWebElement link = x.findFirst("a");
        mecevi m={link.toPlainText(),link.attribute("href"),true};
        spisak.push_back(m);
        //qDebug() << link.toPlainText() << link.attribute("href");
    }
    return true;
}

QList<QString> NkMecevi::getList()
{
    QList<QString> l;
    for(auto x : spisak){

        l.push_back(x.timovi);
    }
    return l;
}

QList<QString> NkMecevi::getLinks()
{
    QList<QString> l;
    for(auto x : spisak){
        if(x.selekted)
            l.push_back(x.link);
    }
    return l;
}

void NkMecevi::clear()
{
    spisak.clear();
}

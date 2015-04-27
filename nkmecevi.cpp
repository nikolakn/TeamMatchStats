/*
* (C) Copyright 2015
* Authors:
* Nikola Knezevic <nkcodeplus@gmail.com>
* Goran Lapčević <gorlap@gmail.com>
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; version 2
* of the License.
*/

#include "nkmecevi.h"
#include <QDebug>
NkMecevi::NkMecevi(QObject *parent) :
    QObject(parent)
{
QStringList list;

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

    if(str.toPlainText().toInt()!=st && st!=1)
        return false;
    //QWebElement result = parse.firstChild();
    QWebElement result = parse.findFirst("table.alternate tbody");
    QWebElementCollection result2 = result.findAll("tr");
    for(QWebElement x : result2){
        //qDebug() << x.toPlainText();
        QWebElementCollection result2 = x.findAll("td");
        QWebElement link = x.findFirst("a");
        QWebElementCollection aaa = x.findAll("a");

        QString a1=result2[2].toPlainText();
        a1=a1.leftJustified(5, ' ');
        QString a2=result2[3].toPlainText();
        //a2=a2.leftJustified(12, ' ');
        QString a3=result2[4].toPlainText();
        QString a4=result2[5].toPlainText();
        Mec m={aaa[2].toPlainText()+" / "+link.toPlainText(),link.attribute("href"),true,a1,a2,a3,a4};

        spisak.push_back(m);

    }
    return true;
}

bool NkMecevi::parsPageUtoku(QString html)
{
    //qDebug() <<html;
    QRegExp rx("<table id=\"c3\"(.+)</table></div> </div>   <div id=\"");
    if (rx.indexIn(html) != -1)
        html = rx.cap(1);
    html="<table "+html+"</table>";
    //qDebug() <<html;
    QWebPage page;
    QWebFrame * frame = page.mainFrame();
    frame->setHtml(html);
    QWebElement parse = frame->documentElement();
    //page num
    //qDebug() <<parse.toPlainText();
    //QWebElement str = parse.findFirst("ul.pagination li.current");
    //qDebug() <<parse.toPlainText();
    //QWebElement result = parse.firstChild();
    QWebElement result = parse.findFirst("tbody");
    QWebElement x = result.findFirst("tr");
    //for(QWebElement x : result2){
        //qDebug() << x.toPlainText();
        QWebElementCollection result2 = x.findAll("td");
        QWebElement link = x.findFirst("a");
        QWebElementCollection aaa = x.findAll("a");
        //qDebug()<<aaa[2].toPlainText();
        //qDebug() <<link.attribute("href");
        QString a1=result2[2].toPlainText();
        a1=a1.leftJustified(5, ' ');
        QString a2=result2[3].toPlainText();
        //a2=a2.leftJustified(12, ' ');
        QString a3=result2[4].toPlainText();
        QString a4=result2[5].toPlainText();
        Mec m={aaa[2].toPlainText()+" / "+link.toPlainText(),link.attribute("href"),true,a1,a2,a3,a4};
        //qDebug()<<result2[2].toPlainText()<<" "<<result2[3].toPlainText()<<" "<<result2[4].toPlainText()<<" "<<result2[5].toPlainText();
        spisak.push_back(m);
        //qDebug() << link.toPlainText() << link.attribute("href");
    //}
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
        //if(x.selekted){
            l.push_back(x.link);
            //return l;
        // }
    }
    return l;
}

void NkMecevi::clear()
{
    spisak.clear();
}

void NkMecevi::addLink(QString naziv,QString ime)
{
    Mec m;
    m.timovi=ime;
    m.link = "/groups/team_match?id="+naziv;
    m.selekted = true;
    spisak.push_back(m);
}

void NkMecevi::unCheckAll()
{
    for(auto &x : spisak){
        x.selekted=false;
    }
}

void NkMecevi::Check(int i)
{
    spisak[i].selekted=true;
}

void NkMecevi::UnCheck(int i)
{
    spisak[i].selekted=false;
}

int NkMecevi::getSelected()
{
    int rez=0;
    for(auto x : spisak){
        if(x.selekted){
            rez++;
        }
    }
    return rez;
}

void NkMecevi::save(QDataStream &out)
{
    out << spisak.size();
    for(auto x : spisak){
        out << x.timovi;
        out << x.link;
        if( x.selekted)
           out << (int)1;
        else
           out << (int)0;
        out << x.tabli << x.rez << x.procenat << x.pobeda;
    }
}

void NkMecevi::open(QDataStream &in)
{
    int ss=0;
    in >> ss;
    Mec m;

    for(int i=0;i<ss;i++){
       in >> m.timovi;

       in >> m.link;
       int tt;
       in >> tt;
       m.selekted=tt;

       in >> m.tabli;
       in >> m.rez;
       in >> m.procenat;
       in >> m.pobeda;

       spisak.push_back(m);

    }

}

void NkMecevi::toggle(int i)
{
    spisak[i].selekted=!spisak[i].selekted;
}

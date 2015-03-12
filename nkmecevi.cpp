/*
* (C) Copyright 2015
* Author: Nikola Knezevic <nkcodeplus@gmail.com>
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

void NkMecevi::addLink(QString naziv)
{
    mecevi m={naziv,"/groups/team_match?id="+naziv,true};
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
        out << x.selekted;
    }
}

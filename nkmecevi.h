/*
* (C) Copyright 2015
* Author: Nikola Knezevic <nkcodeplus@gmail.com>
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; version 2
* of the License.
*/

#ifndef NKMECEVI_H
#define NKMECEVI_H

#include <QObject>
#include <QWebPage>
#include <QWebFrame>
#include <QWebElement>
#include <QVector>
#include <QList>

struct mecevi{
    QString timovi;
    QString link;
    bool selekted;
};

class NkMecevi : public QObject
{
    Q_OBJECT
public:
    explicit NkMecevi(QObject *parent = 0);
    bool parsPage(QString html, int st);
    QList<QString> getList();
    QList<QString> getLinks();
    void clear();
    void addLink(QString naziv);
    void unCheckAll();
    void Check(int i);
    int getSelected();
signals:

private:
    QVector<mecevi> spisak;
};

#endif // NKMECEVI_H

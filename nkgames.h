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

#ifndef NKGAMES_H
#define NKGAMES_H

#include <QObject>
#include <QWebPage>
#include <QWebFrame>
#include <QWebElement>
#include <QVector>
#include <QList>
#include <QTableWidget>

struct players{
    QString Ime;
    int brojOdigranih;
    double bodova;
    int pobeda;
    int poraza;
    double remija;
    double bilans;
    int procenatPobeda;
    long doprinos;
    int rejting;
    int Pzp;
    int Prp;
    int brojzavrsenih;
    int dobijenihmeceva;
    int izgubljenihmeceva;
    int neresenihmeceva;
    QVector<int> reitinziprotivnika;
    QVector<int> reitinziprotivnika2;
};
enum TipColone{CEO_BROJ,DECIMALNI,SLOVA};
struct TableInfo{
    int colona;
    int sirina;
    QString imekolone;
    QColor boja;
    TipColone t;
    int c;
    double d;
    QString s;
};

class NkGames : public QObject
{
    Q_OBJECT
public:
    explicit NkGames(QObject *parent = 0);
    bool parsPage(QString html, QString Tim, int vrsta);
    void print(QTableWidget *resultView);
    void clear();
    //copy table to clipbord
    QString copyToClip();
    QString toolbar();
    QString toExcelXML();
private:
    int nkbrojmeceva;
    QVector<players> igraci;

};

#endif

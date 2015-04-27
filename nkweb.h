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

#ifndef NKWEB_H
#define NKWEB_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QObject>

class NkWeb : public QObject
{
    Q_OBJECT

public:
    NkWeb();
    ~NkWeb();
    void getPage(QString adresa, int i = 0);
    QString get() {return strana;}
    int mi;
public slots:
    void replyFinished(QNetworkReply*);

signals:

    void gotovo();
private:
    QUrl url;
    QNetworkAccessManager *manager;
    QString strana;

};

#endif // NKWEB_H

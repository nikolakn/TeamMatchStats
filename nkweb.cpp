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

#include "nkweb.h"
#include <QMessageBox>
#include <QDebug>
NkWeb::NkWeb()
{
    manager = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(finished(QNetworkReply*)),
             this, SLOT(replyFinished(QNetworkReply*)));
}

NkWeb::~NkWeb()
{
    delete manager;
}

void NkWeb::getPage(QString adresa, int i)
{
    mi = i;
    strana="";
    manager->get(QNetworkRequest(QUrl(adresa)));
}


void NkWeb::replyFinished(QNetworkReply* pReply)
{
    QByteArray data=pReply->readAll();
    QString str(data);
    strana=str;
    //qDebug() << strana;
    emit gotovo();
}

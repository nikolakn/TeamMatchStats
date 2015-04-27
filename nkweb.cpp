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

void NkWeb::getPage(QString adresa, int i, int ind)
{
    mi = i;
    index = ind;
    strana="";
    QNetworkRequest nr;
    QVariant v(ind);
    nr.setAttribute(QNetworkRequest::CustomVerbAttribute,v);
    nr.setUrl(QUrl(adresa));
    manager->get(nr);
}


void NkWeb::replyFinished(QNetworkReply* pReply)
{
    QByteArray data=pReply->readAll();
    QString str(data);
    strana=str;
    QVariant v=pReply->request().attribute(QNetworkRequest::CustomVerbAttribute);
    //qDebug() << v.toInt();
    index = v.toInt();
    emit gotovo();
}

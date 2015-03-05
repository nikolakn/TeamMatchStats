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

void NkWeb::getPage(QString adresa)
{
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

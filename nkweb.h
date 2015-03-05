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
    void getPage(QString adresa);
    QString get() {return strana;}
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

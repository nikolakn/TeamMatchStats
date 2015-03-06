#ifndef NKGAMES_H
#define NKGAMES_H

#include <QObject>
#include <QWebPage>
#include <QWebFrame>
#include <QWebElement>
#include <QWebView>
#include <QVector>
#include <QList>
#include <QTableWidget>
struct players{
    QString Ime;
    int brojOdigranih;
    double bodova;
    int pobeda;
    int poraza;
    int remija;
    int bilans;
    double procenatPobeda;
    long doprinos;
};

class NkGames : public QObject
{
    Q_OBJECT
public:
    explicit NkGames(QObject *parent = 0);
    bool parsPage(QString html, QString Tim);
    void print(QTableWidget *resultView);
    void clear();
    QString copyToClip();
private:
    QVector<players> igraci;

};

#endif

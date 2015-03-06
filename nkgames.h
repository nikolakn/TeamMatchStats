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
    int bodova;
    int pobeda;
    int poraza;
    int remija;
    double procenatPobeda;
};

class NkGames : public QObject
{
    Q_OBJECT
public:
    explicit NkGames(QObject *parent = 0);
    bool parsPage(QString html, QString Tim);
    void print(QTableWidget *resultView);
    void clear();
private:
    QVector<players> igraci;

};

#endif

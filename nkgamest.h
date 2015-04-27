#ifndef NKGAMEST_H
#define NKGAMEST_H


#include <QObject>
#include <QWebPage>
#include <QWebFrame>
#include <QWebElement>
#include <QVector>
#include <QList>
#include <QTableWidget>

struct players2{
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

class NkGamesT : public QObject
{
    Q_OBJECT
public:
    explicit NkGamesT(QObject *parent = 0);
    bool parsPage(QString html, QString Tim, int vrsta);
    static int broj2;
    void clear();
private:
    int nkbrojmeceva;
    QVector<players2> igraci;

};

#endif // NKGAMEST_H

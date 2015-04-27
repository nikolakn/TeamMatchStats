#ifndef NKGAMEST_H
#define NKGAMEST_H


#include <QObject>
#include <QWebPage>
#include <QWebFrame>
#include <QWebElement>
#include <QVector>
#include <QList>
#include <QTableWidget>

struct NkLink{
    QString link;
    QString ime;
    bool beli;
    QString vreme;
    int minita;
    int sati;
};

class NkGamesT : public QObject
{
    Q_OBJECT
public:
    explicit NkGamesT(QObject *parent = 0);
    bool parsPage(QString html, QString Tim, int vrsta);
    static int broj2;
    void clear();
    QList<NkLink> getLinks();
private:
    int nkbrojmeceva;
    QList<NkLink> mlinkovi;


};

#endif // NKGAMEST_H

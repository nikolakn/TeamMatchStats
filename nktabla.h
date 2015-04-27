#ifndef NKTABLA_H
#define NKTABLA_H

#include <QObject>
#include <QWebPage>
#include <QWebFrame>
#include <QWebElement>
#include <QVector>
#include <QList>
#include <QTableWidget>



class NkTabla : public QObject
{
    Q_OBJECT
public:
    explicit NkTabla(QObject *parent = 0);
    bool parsPage(QString html, QString Tim, int vrsta);
    static int broj2;
    void clear();
    QString getRez();
private:
    int nkbrojmeceva;
    QString rez;


};

#endif // NKTABLA_H

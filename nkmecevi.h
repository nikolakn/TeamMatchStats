#ifndef NKMECEVI_H
#define NKMECEVI_H

#include <QObject>
#include <QWebPage>
#include <QWebFrame>
#include <QWebElement>
#include <QVector>
#include <QList>

struct mecevi{
    QString timovi;
    QString link;
    bool selekted;
};

class NkMecevi : public QObject
{
    Q_OBJECT
public:
    explicit NkMecevi(QObject *parent = 0);
    bool parsPage(QString html, int st);
    QList<QString> getList();
    QList<QString> getLinks();
    void clear();
signals:

private:
    QVector<mecevi> spisak;
};

#endif // NKMECEVI_H

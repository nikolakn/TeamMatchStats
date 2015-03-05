#ifndef NKMECEVI_H
#define NKMECEVI_H

#include <QObject>
#include <QWebPage>
#include <QWebFrame>
#include <QWebElement>
#include <QWebView>

class NkMecevi : public QObject
{
    Q_OBJECT
public:
    explicit NkMecevi(QObject *parent = 0);
    void parsPage(QString html);
signals:

public slots:

};

#endif // NKMECEVI_H

#ifndef NKGAMES_H
#define NKGAMES_H

#include <QObject>

class NkGames : public QObject
{
    Q_OBJECT
public:
    explicit NkGames(QObject *parent = 0);
    bool parsPage(QString html, QString Tim);
    void clear();


};

#endif

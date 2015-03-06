#ifndef TABLEITEM_H
#define TABLEITEM_H
#include <QTableWidgetItem>

class TableItem : public QTableWidgetItem
{
public:
    TableItem(const QString & text)
        :
            QTableWidgetItem(text)
    {}

    TableItem(int num)
        :
            QTableWidgetItem(QString::number(num))
    {}

    bool operator< (const QTableWidgetItem &other) const
    {

       return text().toInt() < other.text().toInt();

    }
};
#endif // TABLEITEM_H

#ifndef TABLEITEMDOUBLE_H
#define TABLEITEMDOUBLE_H
#include <QTableWidgetItem>

class TableItemDouble : public QTableWidgetItem
{
public:
    TableItemDouble(const QString & text)
        :
            QTableWidgetItem(text)
    {}

    TableItemDouble(int num)
        :
            QTableWidgetItem(QString::number(num))
    {}

    bool operator< (const QTableWidgetItem &other) const
    {

            return text().toDouble() < other.text().toDouble();

    }
};
#endif // TABLEITEMDOUBLE_H

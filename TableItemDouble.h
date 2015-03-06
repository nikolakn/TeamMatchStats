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
        if (other.column() == 1) {

            // Compare cell data as integers for the second column.
            return text().toDouble() < other.text().toDouble();
        }
        return other.text() < text();
    }
};
#endif // TABLEITEMDOUBLE_H

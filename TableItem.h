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
        if (other.column() == 1) {
            // Compare cell data as integers for the second column.
            return text().toInt() < other.text().toInt();
        }
        return other.text() < text();
    }
};
#endif // TABLEITEM_H

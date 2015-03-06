/*
* (C) Copyright 2015
* Author: Nikola Knezevic <nkcodeplus@gmail.com>
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; version 2
* of the License.
*/

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

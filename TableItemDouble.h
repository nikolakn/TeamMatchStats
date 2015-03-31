/*
* (C) Copyright 2015
* Authors:
* Nikola Knezevic <nkcodeplus@gmail.com>
* Goran Lapčević <gorlap@gmail.com>
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; version 2
* of the License.
*/

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

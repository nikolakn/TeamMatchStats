#ifndef NKTIMEDIALOG_H
#define NKTIMEDIALOG_H

#include <QDialog>
#include "nkweb.h"
#include "nkmecevi.h"
#include "nkgamest.h"
#include <QStandardItemModel>

namespace Ui {
class NkTimeDialog;
}

class NkTimeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NkTimeDialog(QWidget *parent,QString tim,QString adresa);
    ~NkTimeDialog();
    void makeTable();
    void makeList();
public slots:
    void stranicaSpremna();
    void onOK_click();
private slots:
    void on_pushButton_clicked();

private:
    Ui::NkTimeDialog *ui;
    QStandardItemModel *model;
    QStandardItem *Item;
    QStandardItem *Item2;
    QString mtim;
    QString madresa;
    NkWeb web;
    NkMecevi mecevi;
    NkGamesT games;
    bool isGame;
    int kraj;
};

#endif // NKTIMEDIALOG_H

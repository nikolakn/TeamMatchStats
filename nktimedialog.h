#ifndef NKTIMEDIALOG_H
#define NKTIMEDIALOG_H

#include <QDialog>
#include "nkweb.h"
#include "nkmecevi.h"
#include "nkgamest.h"
#include <QStandardItemModel>
#include "nktabla.h"
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
    void buildTable();
public slots:
    void stranicaSpremna();
    void stranicaSpremna2();
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
    int vratio;
    NkTabla tab;
    int vratiotable;
};

#endif // NKTIMEDIALOG_H

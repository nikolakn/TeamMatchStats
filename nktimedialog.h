#ifndef NKTIMEDIALOG_H
#define NKTIMEDIALOG_H

#include <QDialog>
#include "nkweb.h"
#include "nkmecevi.h"
#include "nkgamest.h"

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
public slots:
    void stranicaSpremna();
    void onOK_click();
private slots:
    void on_pushButton_clicked();

private:
    Ui::NkTimeDialog *ui;
    QString mtim;
    QString madresa;
    NkWeb web;
    NkMecevi mecevi;
    NkGamesT games;
    bool isGame;
    int kraj;
};

#endif // NKTIMEDIALOG_H

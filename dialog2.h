#ifndef DIALOG2_H
#define DIALOG2_H

#include <QDialog>

namespace Ui {
class Dialog2;
}

class Dialog2 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog2(QWidget *parent = 0);
    ~Dialog2();

private slots:
    void on_pushButton_clicked();

public:
    int getOdabrano() {return odabrano;}
private:
    Ui::Dialog2 *ui;
    int odabrano;
};

#endif // DIALOG2_H

#ifndef UNOSMECADIALOG_H
#define UNOSMECADIALOG_H

#include <QDialog>

namespace Ui {
class unosmecaDialog;
}

class unosmecaDialog : public QDialog
{
    Q_OBJECT

public:
    explicit unosmecaDialog(QWidget *parent = 0);
    ~unosmecaDialog();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();
public:
    QString getID();
    QString getIme();

private:
    Ui::unosmecaDialog *ui;
};

#endif // UNOSMECADIALOG_H

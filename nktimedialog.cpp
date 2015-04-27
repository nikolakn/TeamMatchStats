#include "nktimedialog.h"
#include "ui_nktimedialog.h"

NkTimeDialog::NkTimeDialog(QWidget *parent,QString tim,QString adresa) :
    QDialog(parent),
    ui(new Ui::NkTimeDialog)
{
    ui->setupUi(this);
    mtim = tim;
    kraj=0;
    madresa = adresa;
    isGame=false;
    model = new QStandardItemModel(0,2,this);
    ui->listView->setModel( model );
    connect(&web, SIGNAL(gotovo()), this, SLOT(stranicaSpremna()));
}

NkTimeDialog::~NkTimeDialog()
{
    delete ui;
}

void NkTimeDialog::onOK_click()
{
    isGame=false;
    kraj=0;
    web.getPage(madresa);
}

void NkTimeDialog::stranicaSpremna()
{
    if(!isGame){
            QString pp=web.get();
            mecevi.parsPageUtoku(pp);
            //makeList();
            isGame = true;
            makeTable();
            return;
    }
    else{
        //lodad page with games
        QString pp=web.get();

        if(games.parsPage(pp,mtim,0)){
            if(kraj==1)
                makeList();
                //games.print(resultView);
            return;
        }
    }
}

void NkTimeDialog::makeTable()
{
    games.clear();
    QList<QString> linkovi=mecevi.getLinks();
    int rez=mecevi.getSelected();
    //qDebug()<<linkovi.size()<<" aaaa "<<rez;
    int i=0;
    int dodato=0;
    for(QString s : linkovi){
            dodato++;
            isGame=true;
            //qDebug()<< dodato<<" !!! "<<rez;
            if(dodato==rez)
                kraj=1;
            web.getPage("http://www.chess.com"+s);

        i++;
    }
}

void NkTimeDialog::on_pushButton_clicked()
{
   onOK_click();
}

void NkTimeDialog::makeList()
{
    int i = 0;
    QList<QString> ll=games.getLinks();
    for(QString s : ll){
        Item = new QStandardItem();

        Item->setText(s);
        model->setItem( i++,0, Item );
    }
}

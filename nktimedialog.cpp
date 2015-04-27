#include "nktimedialog.h"
#include "ui_nktimedialog.h"
#include <qdebug.h>
NkTimeDialog::NkTimeDialog(QWidget *parent,QString tim,QString adresa) :
    QDialog(parent),
    ui(new Ui::NkTimeDialog)
{
    ui->setupUi(this);
    mtim = tim;
    kraj=0;
    vratio = 0;
    vratiotable = 0;
    madresa = adresa;
    isGame=false;
    model = new QStandardItemModel(0,2,this);
    ui->listView->setModel( model );
    //connect(&web, SIGNAL(gotovo()), this, SLOT(stranicaSpremna()));
}

NkTimeDialog::~NkTimeDialog()
{
    delete ui;
}

void NkTimeDialog::onOK_click()
{
    disconnect(&web, SIGNAL(gotovo()), this, SLOT(stranicaSpremna2()));
    connect(&web, SIGNAL(gotovo()), this, SLOT(stranicaSpremna()));
    isGame=false;
    kraj=0;
    vratio = 0;
    vratiotable = 0;
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
        vratio ++;
        if(games.parsPage(pp,mtim,0)){

            if(vratio==mecevi.getList().size())
                buildTable();
                //makeList();
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
    QList<NkLink> ll=games.getLinks();
    for(NkLink s : ll){
        Item = new QStandardItem();
        if(s.beli)
            Item->setText(s.vreme+" "+s.ime + " beli "+s.link);
        else
            Item->setText(s.vreme+" "+s.ime +" crni "+s.link);
        model->setItem( i++,0, Item );
    }
}
void NkTimeDialog::buildTable()
{

    disconnect(&web, SIGNAL(gotovo()), this, SLOT(stranicaSpremna()));
    connect(&web, SIGNAL(gotovo()), this, SLOT(stranicaSpremna2()));
    vratio = 0;
    QList<NkLink> ll=games.getLinks();
    int i=0;
    for(NkLink s : ll){
        web.getPage(s.link, s.beli,i);
        i++;
    }
}

void NkTimeDialog::stranicaSpremna2()
{
    qDebug() << "ulazi";
    QString pp=web.get();
    int mi = web.mi;
    int index =web.index;
    vratiotable ++;
    if(tab.parsPage(pp,mtim,mi)){
        games.setTime(index,tab.getRez());
        if(vratiotable==games.getLinks().size())
            makeList();
            //games.print(resultView);
        return;
    }

}

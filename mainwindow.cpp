#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QWebPage>
#include <QWebFrame>
#include <QWebElement>
#include <QWebView>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    adresaLabel = new QLabel(tr("Adresa:"));
    adresa = new QLineEdit();
    adresa->setText("http://www.chess.com/groups/team_match_archive?id=8083");

    timLabel = new QLabel(tr("Tim:"));
    tim = new QLineEdit();
    tim->setMaximumWidth(80);
    tim->setFixedWidth(100);

    tim->setText("Srbija Tim");
    dugme1 = new QPushButton(tr("Ok"));

    QHBoxLayout *adresaLayout = new QHBoxLayout;
    adresaLayout->addWidget(adresaLabel);
    adresaLayout->addWidget(adresa);
    adresaLayout->addWidget(timLabel);
    adresaLayout->addWidget(tim);
    adresaLayout->addWidget(dugme1);

    QSplitter *splitter = new QSplitter(parent);

    listview = new QListView();
    model = new QStandardItemModel();
    Item = new QStandardItem();
    Item->setCheckable( true );
    Item->setCheckState( Qt::Checked );
    model->setItem( 0, Item );
    listview->setModel( model );

    resultView = new QTableView();

    splitter->addWidget(listview);
    splitter->addWidget(resultView);
    QList<int> a={200,600};
    splitter->setSizes(a);

    QVBoxLayout *mainLayout = new QVBoxLayout(parent);
    mainLayout->addLayout(adresaLayout);
    mainLayout->addWidget(splitter);

    this->centralWidget()->setLayout(mainLayout);
    setWindowTitle(tr("Team Match Stats"));
    connect(dugme1, SIGNAL(clicked()), this, SLOT(onOK_click()));
    connect(&web, SIGNAL(gotovo()), this, SLOT(stranicaSpremna()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onOK_click()
{
    web.getPage(adresa->text());
}

void MainWindow::stranicaSpremna()
{
     QString pp=web.get();

    QRegExp rx("<body>(.+)</body>");
    if (rx.indexIn(pp) != -1)
        pp = rx.cap(1);

    //qDebug()<<pp;



    QWebPage page;
    QWebFrame * frame = page.mainFrame();
    frame->setHtml(pp);
    QWebElement parse = frame->documentElement();

    //QWebElement result = parse.firstChild();
    QWebElement result = parse.findFirst("table.alternate tbody");
    QWebElementCollection result2 = result.findAll("tr");
    for(QWebElement x : result2){
        //QWebElementCollection result2 = result.findAll("td");
        QWebElement link = x.findFirst("a");
         qDebug() << link.toPlainText() << link.attribute("href");
    }
    int numTables = result2.count();
    qDebug() << numTables;


}

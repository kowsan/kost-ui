#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "issueswidget.h"
#include "loginwindow.h"

void MainWindow::init()
{
    nex->setHost(Settings::serverHost());
    nex->setPort(Settings::serverPort());
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    nex=new NetworkExchange(this);
      ui->webView->page()->setNetworkAccessManager(nex->nam);
    init();
    tmr=new QTimer(this);
    tmr->setInterval(20000);
    tmr->start();
   // connect(tmr,SIGNAL(timeout()),nex,SLOT(registerAWS()));
   connect(nex,SIGNAL(workSpaceChanged(QString,QString)),this,SLOT(onARMStatusChanged(QString,QString)));

    nex->registerAWS();



    connect(ui->actionLogin,SIGNAL(triggered(bool)),this,SLOT(showLoginDialog()));
#ifdef Q_OS_OSX
    ui->actionSettings->setShortcut(QKeySequence::Preferences);
#else
    ui->actionSettings->setShortcut(QKeySequence("Ctrl+E"));
#endif
    connect(ui->actionSettings,SIGNAL(triggered(bool)),this,SLOT(showSettings()));
    //nex->login("admin","admin");

}

void MainWindow::onARMStatusChanged(const QString &workSpaceId,const QString &id)
{

//    if (workSpaceId=="0" )
//    {
//        ui->appStackedWidget->setCurrentWidget(ui->nrWidget);
//        ui->nrWidget->setArmId(id);

//    }
//    else
//    {
        this->setWindowTitle(QString("КСОТ: \"Рабочее место\" ID: %1").arg(workSpaceId));
        ui->appStackedWidget->setCurrentWidget(ui->mainview);
        QUrl u;
        qDebug()<<ui->webView->url();

        if (ui->webView->url()==QUrl("about:blank"))
        {
            u.setScheme("http");
            u.setHost(Settings::serverHost());
            u.setPort(Settings::serverPort());
            ui->webView->load(u);
        }
//    }

}


void MainWindow::showSettings()
{
    SettingsDialog dlg;
    if (dlg.exec()==QDialog::Accepted){
        this->init();
    }
}





void MainWindow::showLoginDialog()
{
    LoginWindow lw;
    connect(&lw,SIGNAL(authRequested(QString,QString)),nex,SLOT(login(QString,QString)));
    connect(nex,SIGNAL(userInfoReceived(const UserInfo*)),&lw,SLOT(close()));
    connect(nex,SIGNAL(authFailed()),&lw,SLOT(setErrorState()));
    lw.exec();
}



MainWindow::~MainWindow()
{
    delete ui;
}

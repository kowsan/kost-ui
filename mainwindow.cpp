#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "issueswidget.h"
#include "loginwindow.h"

#include <QCloseEvent>
#include <QMessageBox>
#include <QWebPage>

void MainWindow::init()
{
    nex->setHost(Settings::serverHost());
    nex->setPort(Settings::serverPort());
    m_isDenyClose=false;
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    this->show();
}


void MainWindow::setDenyClose(bool value)
{
    m_isDenyClose=value;

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
    connect(tmr,SIGNAL(timeout()),nex,SLOT(registerAWS()));
    connect(nex,SIGNAL(workSpaceChanged(QString,QString)),this,SLOT(onARMStatusChanged(QString,QString)));
    connect(nex,SIGNAL(denyCloseChanged(bool)),this,SLOT(setDenyClose(bool)));
    connect(nex,SIGNAL(anonymousChanged()),ui->webView,SLOT(reload()));
     connect(nex,SIGNAL(anonymousChanged()),this,SLOT(loadArm()));
     connect(nex,SIGNAL(networkError(QString)),ui->label,SLOT(setText(QString)));
    nex->registerAWS();
    connect(ui->webView->page(),SIGNAL(loadProgress(int)),this,SLOT(showLoadProgress(int)));
    connect(ui->webView->page(),SIGNAL(loadFinished(bool)),this,SLOT(showLoadFinished(bool)));





    connect(ui->actionLogin,SIGNAL(triggered(bool)),this,SLOT(showLoginDialog()));
#ifdef Q_OS_OSX
    ui->actionSettings->setShortcut(QKeySequence::Preferences);
#else
    ui->actionSettings->setShortcut(QKeySequence("Ctrl+E"));
#endif
    connect(ui->actionSettings,SIGNAL(triggered(bool)),this,SLOT(showSettings()));
    //nex->login("admin","admin");

}

void MainWindow::showLoadStart()
{
   ui->progressBar->show();
}

void MainWindow::showLoadFinished(bool ok)
{
   if (ok){
       ui->progressBar->hide();
   } else {
       qDebug()<<"Page load with errors";
   }
}

void MainWindow::showLoadProgress(int progress)
{
 ui->progressBar->setValue(progress);
}

void MainWindow::loadArm()
{
    QUrl u;
    qDebug()<<ui->webView->url();


        u.setScheme("http");
        u.setHost(Settings::serverHost());
        u.setPort(Settings::serverPort());
        ui->webView->load(u);

    //    ui->webView->reload();


}



void MainWindow::closeEvent(QCloseEvent *ev){
    if (m_isDenyClose)
    {
        QMessageBox::warning(this,"Предупреждение","Закрытие приложения запрещено настройками сервера",QMessageBox::Ok);
        ev->ignore();

    } else
    {
        ev->accept();
    }
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
    this->setWindowTitle(QString("КСОТ: \"Рабочее место\" ID: %1 АРМ ID: %2" ).arg(workSpaceId).arg(id));
    ui->appStackedWidget->setCurrentWidget(ui->mainview);
    loadArm();
    //    }

}


void MainWindow::showSettings()
{
    SettingsDialog dlg;
    if (dlg.exec()==QDialog::Accepted){
        tmr->stop();
        this->init();
        tmr->start();
        loadArm();
    }
}

void MainWindow::onDenyCloseChanged(bool isDeny)
{
    m_isDenyClose=isDeny;
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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "issueswidget.h"
#include "loginwindow.h"

#include <QCloseEvent>
#include <QMessageBox>

void MainWindow::init()
{
    nex->setHost(Settings::serverHost());
    nex->setPort(Settings::serverPort());
    m_isDenyClose=false;
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
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

void MainWindow::loadArm()
{
    QUrl u;
    qDebug()<<ui->webView->url();

    if (ui->webView->url()==QUrl("about:blank"))
    {
        u.setScheme("http");
        u.setHost(Settings::serverHost());
        u.setPort(Settings::serverPort());
        ui->webView->load(u);
    } else {
        ui->webView->reload();
    }

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
        this->init();
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

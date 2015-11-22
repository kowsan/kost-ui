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
    ui->iconLabel->hide();

}


void MainWindow::setDenyClose(bool value)
{
    m_isDenyClose=value;

}

void MainWindow::onFileRequest(QNetworkReply* reply){


    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();


    if (reply->header(QNetworkRequest::ContentTypeHeader).toString()=="application/pdf")
    {

        QTemporaryFile tf;
        qDebug()<<"pdf downloading";
        QByteArray ba=reply->readAll();
        qDebug()<<"Sz :"<<ba.size();
        QString fn=reply->request().url().path().replace("/","_");;
        qDebug()<<fn;
        QString z;
        tf.setAutoRemove(false);
        if(tf.open())
        {
            z=tf.fileName();
            qDebug()<<z;
            tf.write(ba);

        }
        tf.close();
        QDir d;
        d.mkpath(Settings::saveFilesPath());
        tf.copy(Settings::saveFilesPath()+"/"+fn);
        tf.remove();
    }

}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->restoreGeometry(Settings::geometry());
    this->restoreState(Settings::state());
    connect(ui->actionSettings,SIGNAL(triggered(bool)),this,SLOT(showSettings()));
    ui->progressBar->hide();
    nex=new NetworkExchange(this);

    ui->webView->page()->setNetworkAccessManager(nex->nam);
    connect(ui->webView->page(),SIGNAL(unsupportedContent(QNetworkReply*)),this,SLOT(onFileRequest(QNetworkReply*)));
    ui->webView->page()->setForwardUnsupportedContent(true);
    init();
    tmr=new QTimer(this);
    tmr->setInterval(20000);
    tmr->start();
    connect(tmr,SIGNAL(timeout()),nex,SLOT(registerAWS()));
    connect(nex,SIGNAL(workSpaceChanged(QString,QString)),this,SLOT(onARMStatusChanged(QString,QString)));
    connect(nex,SIGNAL(denyCloseChanged(bool)),this,SLOT(setDenyClose(bool)));
    connect(nex,SIGNAL(anonymousChanged()),ui->webView,SLOT(reload()));
    connect(nex,SIGNAL(anonymousChanged()),this,SLOT(loadArm()));
    connect(nex,SIGNAL(networkError(QString)),this,SLOT(onNetworkError(QString)));
    connect(nex,SIGNAL(networkOk()),this,SLOT(onNetworkOk()));


    nex->registerAWS();
    connect(ui->webView->page(),SIGNAL(loadProgress(int)),this,SLOT(showLoadProgress(int)));
    connect(ui->webView->page(),SIGNAL(loadFinished(bool)),this,SLOT(showLoadFinished(bool)));





    connect(ui->actionLogin,SIGNAL(triggered(bool)),this,SLOT(showLoginDialog()));
#ifdef Q_OS_OSX
    ui->actionSettings->setShortcut(QKeySequence::Preferences);
#else
    ui->actionSettings->setShortcut(QKeySequence("Ctrl+E"));
#endif

    //nex->login("admin","admin");

}

void MainWindow::onNetworkOk()
{
    ui->statusLabel->setText(QString("Соединение установлено (%1:%2)").arg(Settings::serverHost()).arg(Settings::serverPort()));
    QPixmap px;
    px.load(":/res/free-23-128.png");
    ui->iconLabel->setPixmap(px);

}


void MainWindow::onNetworkError(QString error)
{
    error="<span style='color:red'>"+error+"</span>";
    ui->statusLabel->setText(QString(error+"(%1:%2)").arg(Settings::serverHost()).arg(Settings::serverPort()));
    QPixmap px;
    px.load(":/res/698395-icon-131-cloud-error-128.png");

    ui->iconLabel->setPixmap(px);
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
    Settings::saveGeometry(this->saveGeometry());
    Settings::saveState(this->saveState());
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

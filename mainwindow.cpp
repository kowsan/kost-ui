#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "issueswidget.h"
#include "loginwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    nex=new NetworkExchange(this);
    nex->setHost("127.0.0.1");
    nex->setPort(3000);
    tmr=new QTimer(this);
    tmr->setInterval(20000);
    tmr->start();
    connect(tmr,SIGNAL(timeout()),nex,SLOT(getSettings()));
    connect(nex,SIGNAL(userInfoReceived(const UserInfo*)),this,SLOT(rebuildUserSpace(const UserInfo*)));
    connect(nex,SIGNAL(anonymousModeChanged(bool)),this,SLOT(showHideAnonymous(bool)));
    nex->getSettings();
    //nex->login("admin","admin");

}

void MainWindow::rebuildUserSpace(const UserInfo *uinfo){
    //Manage User section
    qDebug()<<"perm processed";
    QList <UserWidget*> iw=ui->tabWidget->findChildren<UserWidget*> ();
    if (uinfo->canManageOrgStructure) {

        if (iw.count()==0){
            UserWidget *iw = new UserWidget(ui->tabWidget);

            ui->tabWidget->addTab(iw,"Пользователи");
        }
    } else {
        if (iw.count()>0) {
            // iw.first()->deleteLater();// deleteLater();
            qDeleteAll(iw);
            iw.clear();
        }
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

void MainWindow::showHideAnonymous(bool e)
{

    QList <IssuesWidget*> iw=ui->tabWidget->findChildren<IssuesWidget*> ();
    if (e) {

        if (iw.count()==0){
            IssuesWidget *iw = new IssuesWidget(ui->tabWidget);
            connect(iw,SIGNAL(loginRequested()),this,SLOT(showLoginDialog()));
            ui->tabWidget->insertTab(0,iw,"Нарушения");
        }
    } else {
        if (iw.count()>0) {
            // iw.first()->deleteLater();// deleteLater();
            qDeleteAll(iw);
            iw.clear();
        }
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}

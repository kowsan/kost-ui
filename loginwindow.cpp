#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    ui->errorLabel->hide();
    connect(ui->cancelButton,SIGNAL(clicked(bool)),this,SLOT(reject()));
       connect(ui->okButton,SIGNAL(clicked(bool)),this,SLOT(onAuthRequested()));
}


void LoginWindow::setErrorState()
{
  ui->errorLabel->show();
}

void LoginWindow::onAuthRequested()
{
    ui->errorLabel->hide();
    emit authRequested(ui->loginEdit->text(),ui->passwordEdit->text());
}


LoginWindow::~LoginWindow()
{
    delete ui;
}

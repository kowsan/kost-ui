#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "settings.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    this->setWindowIcon(QIcon(":/res/1433976584_services.png"));
    ui->serverEdit->setText(Settings::serverHost());
    ui->portEdit->setValue(Settings::serverPort());
connect(this,SIGNAL(accepted()),this,SLOT(save()));
}



void SettingsDialog::save(){

     Settings::setServerHost(ui->serverEdit->text());
     Settings::setServerPort(ui->portEdit->value());
}
SettingsDialog::~SettingsDialog()
{
    delete ui;
}

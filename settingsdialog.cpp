#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "settings.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    this->setFixedSize(this->size());
    this->setWindowIcon(QIcon(":/res/1433976584_services.png"));
    ui->serverEdit->setText(Settings::serverHost());
    ui->portEdit->setValue(Settings::serverPort());
    ui->storagePath->setText(QDir::toNativeSeparators(Settings::saveFilesPath()));
    connect(ui->selectFolder,SIGNAL(clicked(bool)),this,SLOT(getSaveFolder()));
    connect(this,SIGNAL(accepted()),this,SLOT(save()));
}


void SettingsDialog::getSaveFolder()
{


    QString dir = QFileDialog::getExistingDirectory(this, "Выбор папки",
                                                    QDir::homePath(),
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    if (!dir.isEmpty())
    {


        ui->storagePath->setText(QDir::toNativeSeparators(dir));
    }
}
void SettingsDialog::save(){

    Settings::setServerHost(ui->serverEdit->text());
    Settings::setServerPort(ui->portEdit->value());
    if (ui->autoStartGip->isChecked())
    {
        Settings::setAutostartWin(true);
    }
    else
    {
        Settings::setAutostartWin(false);
    }

    Settings::setSaveFolder(QDir::fromNativeSeparators(ui->storagePath->text()));
}
SettingsDialog::~SettingsDialog()
{
    delete ui;
}

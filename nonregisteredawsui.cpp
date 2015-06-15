#include "nonregisteredawsui.h"
#include "ui_nonregisteredawsui.h"

NonRegisteredAWSUi::NonRegisteredAWSUi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NonRegisteredAWSUi)
{
    ui->setupUi(this);
}

NonRegisteredAWSUi::~NonRegisteredAWSUi()
{
    delete ui;
}

void NonRegisteredAWSUi::setArmId(QString armId)
{
    if (m_armId == armId)
        return;

    m_armId = armId;
    ui->label_2->setText(ui->label_2->text().arg(m_armId));

    emit armIdChanged(armId);
}

#include "issueswidget.h"
#include "ui_issueswidget.h"

IssuesWidget::IssuesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IssuesWidget)
{
    ui->setupUi(this);
    connect(ui->loginButton,SIGNAL(clicked(bool)),this,SIGNAL(loginRequested()));
}

IssuesWidget::~IssuesWidget()
{
    delete ui;
}

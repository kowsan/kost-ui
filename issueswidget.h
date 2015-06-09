#ifndef ISSUESWIDGET_H
#define ISSUESWIDGET_H

#include <QWidget>

namespace Ui {
class IssuesWidget;
}

class IssuesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IssuesWidget(QWidget *parent = 0);
    ~IssuesWidget();
signals:
    void loginRequested();

private:
    Ui::IssuesWidget *ui;
};

#endif // ISSUESWIDGET_H

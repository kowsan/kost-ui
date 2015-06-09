#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "networkexchange.h"
#include "userwidget.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void showHideAnonymous(bool e);
    void showLoginDialog();
    void rebuildUserSpace(const UserInfo *ui);
private:
    Ui::MainWindow *ui;
    NetworkExchange *nex;
    QTimer *tmr;
};

#endif // MAINWINDOW_H

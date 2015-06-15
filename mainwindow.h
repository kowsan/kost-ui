#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "networkexchange.h"
#include "nonregisteredawsui.h"
#include "settingsdialog.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void init();
private slots:

    void showLoginDialog();

    void showSettings();
    void onARMStatusChanged(const QString &workSpaceId, const QString &id);
private:
    Ui::MainWindow *ui;
    NetworkExchange *nex;
    QTimer *tmr;
};

#endif // MAINWINDOW_H

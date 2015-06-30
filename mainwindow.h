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
    void loadARM(QUrl u);
    void loadArm();
private slots:

    void showLoginDialog();

    void showSettings();
    void onDenyCloseChanged(bool isDeny);
    void onARMStatusChanged(const QString &workSpaceId, const QString &id);
    void setDenyClose(bool value);
private:
    Ui::MainWindow *ui;
    NetworkExchange *nex;
    QTimer *tmr;
    bool m_isDenyClose;
    void closeEvent(QCloseEvent *ev);
};

#endif // MAINWINDOW_H

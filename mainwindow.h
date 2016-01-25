#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "networkexchange.h"
#include "nonregisteredawsui.h"
#include "settingsdialog.h"
#include <QPixmap>


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
    void checkAssignedIssues();
    void showLoginDialog();
    void loadArm();
    // void loadARM(QUrl u);
    void showSettings();
    void onDenyCloseChanged(bool isDeny);
    void onARMStatusChanged(const QString &workSpaceId, const QString &id);
    void setDenyClose(bool value);
    void showLoadProgress(int progress);
    void showLoadFinished(bool ok);
    void showLoadStart();
    void onNetworkError(QString error);
    void onNetworkOk();
    void onFileRequest(QNetworkReply *reply);
    void onLinkClicked(QUrl u);
private:
    Ui::MainWindow *ui;
    NetworkExchange *nex;
    QTimer *tmr;
    bool m_isDenyClose;
    void closeEvent(QCloseEvent *ev);
};

#endif // MAINWINDOW_H

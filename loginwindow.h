#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();
public slots:
    void onAuthRequested();
signals:
    void authRequested(const QString &login,const QString &password);
private slots:
    void setErrorState();
private:
    Ui::LoginWindow *ui;
};

#endif // LOGINWINDOW_H

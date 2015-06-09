#ifndef NETWORKEXCHANGE_H
#define NETWORKEXCHANGE_H

#include <QObject>
#include <QtNetwork>
#include "settings.h"
#include <QJsonObject>
#include <QJsonDocument>

class UserInfo
{
public:
    UserInfo() {

    }
    QString firstName;
    QString lastName;
    QString middleName;
    bool canAddIssue;
    bool canEditIssue;
    bool canChangeIssueStatus;
    bool canShutdownApp;
    bool canViewIssueReportLocal;
    bool canViewEmployeesList;
    bool canViewIssueReportOwned;
    bool canViewAwsListOwned;
    bool canViewWorkChangesOwned;
    bool canFillControlList;
    bool canManageOrgStructure;


};


class NetworkExchange : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString host READ host WRITE setHost NOTIFY hostChanged)
    Q_PROPERTY(qint16 port READ port WRITE setPort NOTIFY portChanged)
    Q_PROPERTY(bool allowAnonymous READ allowAnonymous  NOTIFY anonymousModeChanged)

public:
    explicit NetworkExchange(QObject *parent = 0);

    QString host() const
    {
        return m_host;

    }

    qint16 port() const
    {
        return m_port;
    }

    bool allowAnonymous() const
    {
        return m_allowAnonymous;
    }
    const UserInfo* userInfo(){
        return ui;
    }

signals:
    void hostChanged(QString host);
    void anonymousModeChanged(bool allow);
    void portChanged(qint16 port);
    void userInfoReceived(const UserInfo *ui);
    void authFailed();
private slots:
    void getUserInfo();
private:
    UserInfo *ui;
    QNetworkAccessManager *nam;
    QString m_host;
    qint16 m_port;
    QNetworkCookieJar *cj;
    bool m_allowAnonymous;

    QTimer *tmr;
public slots:
    void setHost(QString host)
    {
        if (m_host == host)
            return;

        m_host = host;
        emit hostChanged(host);
    }
    void setPort(qint16 port)
    {
        if (m_port == port)
            return;

        m_port = port;
        emit portChanged(port);
    }
    void getSettings();
    void login(QString login, QString password);
};

#endif // NETWORKEXCHANGE_H

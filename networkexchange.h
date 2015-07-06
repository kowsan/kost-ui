#ifndef NETWORKEXCHANGE_H
#define NETWORKEXCHANGE_H

#include <QObject>
#include <QtNetwork>
#include "settings.h"
#include <QJsonObject>
#include <QJsonDocument>



class NetworkExchange : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString host READ host WRITE setHost NOTIFY hostChanged)
    Q_PROPERTY(qint16 port READ port WRITE setPort NOTIFY portChanged)


public:
    explicit NetworkExchange(QObject *parent = 0);
    QNetworkAccessManager *nam;
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



signals:
    void anonymousChanged();
    void hostChanged(QString host);
    void workSpaceChanged(QString wsid,QString armId);
    void portChanged(qint16 port);
    void denyCloseChanged(bool isDeny);
    void networkError( QString error);
private slots:

private:
    int m_armId,m_workSpaceId ;
    bool m_allowAnonymous;

    QString m_host;
    qint16 m_port;
    QNetworkCookieJar *cj;


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
    void registerAWS();

};

#endif // NETWORKEXCHANGE_H

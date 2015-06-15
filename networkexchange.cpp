#include "networkexchange.h"

NetworkExchange::NetworkExchange(QObject *parent) : QObject(parent)
{
    m_allowAnonymous=false;
    nam=new QNetworkAccessManager(this);
    tmr=new QTimer(this);
    tmr->setInterval(10000);
    tmr->start();

}





void NetworkExchange::registerAWS()
{
    QNetworkRequest req;
    QUrl u;
    u.setScheme("http");
    u.setHost(m_host);
    u.setPort(m_port);
    u.setPath("/work/app_login.json");
    QUrlQuery qq;
    qq.addQueryItem("app_id",Settings::appId());
    qq.addQueryItem("os",QSysInfo::prettyProductName());
    qq.addQueryItem("name",QHostInfo::localHostName());
    QString u_name = qgetenv("USER");
    if (u_name.isEmpty())
        u_name = qgetenv("USERNAME");
    qDebug() <<"curetn user name"<< u_name;
    qq.addQueryItem("os_user",u_name);
    u.setQuery(qq);
    req.setUrl(u);
    QNetworkReply *reply= nam->get(req);
    QEventLoop loop;
    connect(reply,SIGNAL(finished()),&loop,SLOT(quit()));
    loop.exec();
    QByteArray ba=reply->readAll();
    int sc=reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug()<<"server response"<<reply->errorString()<<ba<<sc;
    if (sc==201)
    {
        QJsonDocument d=QJsonDocument::fromJson(ba);
        int wsid=d.object().value("work_space_id").toInt();
        int armid=d.object().value("id").toInt();
        qDebug()<<"work_space_id:"<<wsid<<"arm id"<<armid;
        emit workSpaceChanged(QString::number(wsid),QString::number(armid));
        return;

    }
}








#include "networkexchange.h"

NetworkExchange::NetworkExchange(QObject *parent) : QObject(parent)
{
    m_allowAnonymous=false;
    nam=new QNetworkAccessManager(this);
    connect(nam,SIGNAL(finished(QNetworkReply*)),this,SLOT(OkorErrror(QNetworkReply*)));


            //connect(nam->,SIGNAL())
            m_armId=0;
            m_workSpaceId=0;
    m_allowAnonymous=NULL;


}




void NetworkExchange::OkorErrror(QNetworkReply *reply)
{
    if (reply->error()==QNetworkReply::NoError)
    {
        emit networkOk();
    }
    else
    {
        emit networkError(reply->errorString());
    }
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
    if (reply->error()==QNetworkReply::NoError)
    {

        // emit networkOk();
        QByteArray ba=reply->readAll();
        int sc=reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qDebug()<<"server response"<<reply->errorString()<<ba<<sc;
        if (sc==201)
        {
            QJsonDocument d=QJsonDocument::fromJson(ba);
            int wsid=d.object().value("work_space_id").toInt();
            int armid=d.object().value("id").toInt();
            bool deny_close=d.object().value("deny_close").toBool(false);
            emit denyCloseChanged(deny_close);
            qDebug()<<"work_space_id:"<<wsid<<"arm id"<<armid;


            if (m_armId != armid || m_workSpaceId!=wsid)
            {
                m_armId=armid;
                m_workSpaceId=wsid;
                emit workSpaceChanged(QString::number(wsid),QString::number(armid));
            }
            bool _allowAnon=d.object().value("allow_anonymous").toBool(false);
            if (_allowAnon!= m_allowAnonymous)
            {
                emit anonymousChanged();
                m_allowAnonymous=_allowAnon;
            }

            return;

        }
    }
    else
    {
        // emit networkError(reply->errorString());
    }
    //reply->deleteLater();
}








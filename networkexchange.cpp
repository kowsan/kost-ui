#include "networkexchange.h"

NetworkExchange::NetworkExchange(QObject *parent) : QObject(parent)
{
    m_allowAnonymous=false;
    nam=new QNetworkAccessManager(this);
    tmr=new QTimer(this);
    tmr->setInterval(10000);
    tmr->start();
    // connect(tmr,SIGNAL(timeout()),this,SLOT(getUserInfo()));
}




void NetworkExchange::getSettings()
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
        bool alanonym=d.object().value("allow_anonymous").toBool(false);
        qDebug()<<"anon:"<<alanonym;
        emit anonymousModeChanged(alanonym);
        return;
        if (m_allowAnonymous!=alanonym)
        {
            m_allowAnonymous=alanonym;

        }
    }
}



void NetworkExchange::login(QString login,QString password)
{
    QNetworkRequest req;
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    //req.setHeader(QNetworkRequest);
    QUrl u;
    u.setScheme("http");
    u.setHost(m_host);
    u.setPort(m_port);
    u.setPath("/users/sign_in");
    req.setUrl(u);
    QUrlQuery qq;
    qq.addQueryItem("user[login]",login);
    qq.addQueryItem("user[password]",password);
    qq.addQueryItem("user[remember_me]","1");

    //u.setQuery(qq);


    QNetworkReply *reply= nam->post(req,qq.query().toLatin1());
    QEventLoop loop;
    connect(reply,SIGNAL(finished()),&loop,SLOT(quit()));
    loop.exec();
    QByteArray ba=reply->readAll();
    int sc=reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug()<<"server response"<<reply->errorString()<<ba<<sc;
    if (sc==302)
    {
        qDebug()<<"WOW auth OK";
        this->getUserInfo();
        //

    }
    if (sc==200)
    {
        emit authFailed();
    }
}

void NetworkExchange::getUserInfo()
{

    ui=new UserInfo();
    QNetworkRequest req;
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QUrl u;
    u.setScheme("http");
    u.setHost(m_host);
    u.setPort(m_port);
    u.setPath("/work/user_info.json");
    req.setUrl(u);



    QNetworkReply *reply= nam->get(req);
    QEventLoop loop;
    connect(reply,SIGNAL(finished()),&loop,SLOT(quit()));
    loop.exec();
    QByteArray ba=reply->readAll();
    int sc=reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug()<<"server response"<<reply->errorString()<<ba<<sc;
    if (sc==200)
    {

        QJsonDocument jd=QJsonDocument::fromJson(ba);
        if (jd.isObject())
        {
            QJsonObject o =jd.object();
            ui->firstName=o.value("first_name").toString();
            ui->lastName=o.value("last_name").toString();
            ui->middleName=o.value("middle_name").toString();

            QJsonObject gp=o.value("staff_role").toObject();
            ui->canAddIssue=gp.value("can_add_issue").toBool(false);
            ui->canEditIssue=gp.value("can_edit_issue").toBool(false);
            ui->canChangeIssueStatus=gp.value("can_change_issue_status").toBool(false);
            ui->canShutdownApp=gp.value("can_shutdown_app").toBool(false);
            ui->canViewIssueReportLocal=gp.value("can_view_issue_report_local").toBool(false);
            ui->canViewEmployeesList=gp.value("can_view_employees_list").toBool(false);
            ui->canViewIssueReportOwned=gp.value("can_view_issue_report_owned").toBool(false);
            ui->canViewAwsListOwned=gp.value("can_view_aws_list_owned").toBool(false);
            ui->canViewWorkChangesOwned=gp.value("can_view_work_changes_owned").toBool(false);
            ui->canFillControlList=gp.value("can_fill_control_list").toBool(false);
            ui->canManageOrgStructure=gp.value("can_manage_org_structure").toBool(false);
            emit userInfoReceived(ui);



        }
    }

}

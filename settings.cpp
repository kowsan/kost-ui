#include "settings.h"

QString appPath()
{
    
    return qApp->applicationFilePath()+".cfg";
}



QString Settings::appId()
{

   QSettings sets(appPath(),QSettings::IniFormat);
   QString appId= sets.value("appid","").toString();
   if(appId.isEmpty()){
       qDebug()<<"App id is empty-creating it";
       appId=QUuid::createUuid().toString();
       sets.setValue("appid",appId);
   }
   return appId;

}

QString Settings::serverHost()
{
   QSettings sets(appPath(),QSettings::IniFormat);
   return sets.value("serverhost","127.0.0.1").toString();
}

qint16 Settings::serverPort()
{
   QSettings sets(appPath(),QSettings::IniFormat);
   return sets.value("serverport","3000").toInt();
}

void Settings::setServerHost(const QString &host)
{
    QSettings sets(appPath(),QSettings::IniFormat);
    sets.setValue("serverhost",host);
}

void Settings::setServerPort(const qint16 &port)
{
    QSettings sets(appPath(),QSettings::IniFormat);
     sets.setValue("serverport",port);
}

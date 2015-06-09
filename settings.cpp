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


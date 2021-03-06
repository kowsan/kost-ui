#include "settings.h"

#include <QDesktopServices>

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
bool Settings::isAutostartWinEnabled()
{
    QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run",QSettings::NativeFormat);
    return settings.value("ksotui","").toString().size()>0;
}

QString Settings::saveFilesPath(){
    QSettings sets(appPath(),QSettings::IniFormat);
    return sets.value("storagepath", QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).first()+"/"+"KSOT").toString();

}

void Settings::setSaveFolder(const QString &folder)
{
    QSettings sets(appPath(),QSettings::IniFormat);
   sets.setValue("storagepath", folder);
}

void Settings::setAutostartWin(const bool &startupEnabled)
{
    QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run",QSettings::NativeFormat);
    if (startupEnabled) {
        settings.setValue("ksotui", "\""+QDir::toNativeSeparators(qApp->applicationFilePath())+"\"");
    } else {
        settings.remove("ksotui");

    }
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

void Settings::saveGeometry(const QByteArray &geom)
{
    QSettings sets(appPath(),QSettings::IniFormat);
    sets.setValue("geometry",geom);
}

void Settings::saveState(const QByteArray &geom)
{
    QSettings sets(appPath(),QSettings::IniFormat);
    sets.setValue("state",geom);
}

QByteArray Settings::geometry()
{
    QSettings sets(appPath(),QSettings::IniFormat);
    return sets.value("geometry",QByteArray()).toByteArray();
}

QByteArray Settings::state()
{
    QSettings sets(appPath(),QSettings::IniFormat);
    return sets.value("state",QByteArray()).toByteArray();
}

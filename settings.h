#ifndef SETTINGS_H
#define SETTINGS_H
#include <QtCore>
#include <QSettings>

class Settings
{
public:
    static QString appId();
    static QString serverHost();
    static qint16 serverPort();
    static void setServerHost(const QString &host);

    static void setServerPort(const qint16 &port);

    static  void setAutostartWin(const bool &startupEnabled);
    static bool isAutostartWinEnabled();
};

#endif // SETTINGS_H

#ifndef SETTINGS_H
#define SETTINGS_H
#include <QtCore>
#include <QSettings>
#include <QStandardPaths>

class Settings
{
public:
    static QString appId();
    static QString serverHost();
    static qint16 serverPort();
    static void setServerHost(const QString &host);

    static void setServerPort(const qint16 &port);
    static void saveGeometry(const QByteArray &geom);
    static void saveState(const QByteArray &geom);


    static QByteArray geometry();
    static QByteArray state();
    static  void setAutostartWin(const bool &startupEnabled);
    static bool isAutostartWinEnabled();
    static QString saveFilesPath();
    static void setSaveFolder(const QString &folder);
};

#endif // SETTINGS_H

#ifndef PROJECT_H
#define PROJECT_H

#include <QString>
#include <QStringList>
#include <QDir>
#include <QMap>

#include "lirc.h"
#include "device.h"

class Project
{
public:
    Project();
    static QString PathToProject;
    static const QString ImagesDirectory;
    static QString LircdConfPath(){return PathToProject + m_LircdConfPath;}

    static QStringList GetImages();

    static QStringList GetLircComands(QString name);
    static QStringList GetLircDevices();
    static Lirc *GetLirc(QString name);

    static void AddDevice(Device *device);
    static QStringList GetDevices();
    static QStringList GetDeviceCommands(QString deviceName);

private:
    static const QString m_LircdConfPath;
    static QMap<QString, Lirc *> m_lircConfiges;
    static QMap<QString, Device*> m_devices;
    static void updateLircConfiges();

};

#endif // PROJECT_H

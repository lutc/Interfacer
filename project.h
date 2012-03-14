#ifndef PROJECT_H
#define PROJECT_H
#include <QObject>
#include <QString>
#include <QStringList>
#include <QDir>
#include <QMap>
#include <QMutex>

#include "lirc.h"
#include "device.h"

class Project : public QObject
{
    Q_OBJECT

public:
    static Project *Instance();

    static QString PathToProject;
    static const QString ImagesDirectory;
    static const QString ControllerDirectory;
    static QString LircdConfPath(){return PathToProject + m_LircdConfPath;}

    static QStringList GetImages();

    static QStringList GetLircComands(QString name);
    static QStringList GetLircDevices();
    static Lirc *GetLirc(QString name);

    void AddDevice(Device *device);
    static QStringList GetDevices();
    static Device *GetDevice(QString deviceName);
    static QStringList GetDeviceCommands(QString deviceName);
    static void GenerateDevicesFile();

    bool ParseDevice(QString rawData);


private:
    static const QString m_LircdConfPath;
    static QMap<QString, Lirc *> m_lircConfiges;
    static QMap<QString, Device*> m_devices;
    static void updateLircConfiges();
    static void generateDeviceFile(Device *device);


    Project();
    Project(const Project&);
    Project& operator =(const Project&);

    static Project* m_instance;

signals:
    void DevicesUpdated(QStringList);

};

#endif // PROJECT_H

#include <QTextStream>
#include "project.h"
#include "parser.h"
#include <QDebug>
#include "pjlinkdevice.h"

#include "comdevice.h"

QString Project::PathToProject = "/home/lutc/MECS/projects/petrogradsk.adm/rootfs/";
const QString Project::m_LircdConfPath = "etc/lirc/lircd.conf";

const QString Project::ImagesDirectory = QString("/Images");
const QString Project::ControllerDirectory = QString("/controller");
QMap<QString, Lirc *> Project::m_lircConfiges;
QMap<QString, Device*> Project::m_devices;

Project* Project::m_instance = 0;

Project::Project()
{
}


QStringList Project::GetImages()
{
    QDir *dir = new QDir(Project::PathToProject + Project::ImagesDirectory);

    // TODO throw exception
    //if (!dir->exists())
    //    throw ;
//    dir->setFilter(QDir::NoDot | QDir::NoDotDot);
    QStringList list = dir->entryList();
    list.removeFirst();
    list.removeFirst();
    return list;
}

QStringList Project::GetLircComands(QString name)
{
    if (m_lircConfiges.isEmpty())
        Project::updateLircConfiges();

    if (Project::m_lircConfiges.contains(name))
    {
        return Project::m_lircConfiges.value(name)->GetCommands();
    }
    return QStringList();
}

QStringList Project::GetLircDevices()
{
    if (m_lircConfiges.isEmpty())
        Project::updateLircConfiges();
    return QStringList(m_lircConfiges.keys());
}

Lirc *Project::GetLirc(QString name)
{
    if (m_lircConfiges.isEmpty())
        Project::updateLircConfiges();

    if (Project::m_lircConfiges.contains(name))
    {
        return Project::m_lircConfiges.value(name);
    }
    return NULL;
}

void Project::updateLircConfiges()
{
    QStringList list = Parser::Parse(Project::LircdConfPath(), Lirc::CommandSeparator);

    foreach (QString rawString, list)
    {
//        QString rawString = list.last();
        Lirc *lirc = new Lirc();
        lirc->Parse(rawString);
        m_lircConfiges[lirc->Name()] = lirc;
    }
}

void Project::generateDeviceFile(Device *device)
{
    QFile file(device->GetFileName());
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
//    out.setCodec("Windows-1251");
    out << device->Save();
    file.close();
}

void Project::AddDevice(Device *device)
{
    m_devices.insert(device->GetName(), device);
    emit DevicesUpdated(Project::GetDevices());
}


QStringList Project::GetDevices()
{
    if (m_devices.isEmpty())
        return QStringList();

    return QStringList(m_devices.keys());
}

Device *Project::GetDevice(QString deviceName)
{
    return m_devices[deviceName];
}

QStringList Project::GetDeviceCommands(QString deviceName)
{
    if (m_devices.contains(deviceName))
        return m_devices[deviceName]->GetCommands();
    return QStringList();
}

void Project::GenerateDevicesFile()
{
    foreach (Device *device, m_devices) {
        generateDeviceFile(device);
    }
}


Project *Project::Instance()
{
    static QMutex mutex;
    if (!m_instance)
    {
        mutex.lock();
        if (!m_instance)
            m_instance = new Project;
        mutex.unlock();
    }
    return m_instance;
}

bool Project::ParseDevice(QString rawData)
{
    if (!rawData.startsWith("protocol"))
        return false;

    QRegExp rawType("protocol (\\w+): (\\w+)");
    rawType.indexIn(rawData, 0);
    Device *parsedDevice;
    QString type = rawType.cap(2);
    QString name = rawType.cap(1);
    if (type.compare("com") == 0)
    {
        QRegExp rawPort("port: (0|1)");
        rawPort.indexIn(rawData, 0);
        QString port = rawPort.cap(1);

        QRegExp rawSpeed("speed: (\\d+)");
        rawSpeed.indexIn(rawData, 0);
        QString speed = rawSpeed.cap(1);

        QRegExp rawcharacterSize("character-size: (\\d+)");
        rawcharacterSize.indexIn(rawData, 0);
        QString characterSize = rawcharacterSize.cap(1);

        QRegExp rawParity("parity: (none|.+\r\n)");
        rawParity.indexIn(rawData, 0);
        QString parity = rawParity.cap(1);

        parsedDevice = new ComDevice(name, port, speed, parity, characterSize);

        int i = 0;
        QRegExp rawMethod("command (\\w+)\n\\{\n\\s+send \\w+ \\(([^\n]+)\\)");
        while ((i = rawMethod.indexIn(rawData, i)) > 0)
        {
            i += rawMethod.matchedLength();

            parsedDevice->addCommand(rawMethod.cap(1), rawMethod.cap(2));
        }

        this->AddDevice(parsedDevice);
    }
    else if (type.compare("tcp") == 0)
    {
        QRegExp rawTargetIp("target-ip: \"([\\d|\\.]+)\\:(\\d+)");
        rawTargetIp.indexIn(rawData, 0);

        QString targetIp = rawTargetIp.cap(1);
        QString targetPort = rawTargetIp.cap(2);

        parsedDevice = new PJLinkDevice(name, targetIp, targetPort);

        int i = 0;
        QRegExp rawMethod("command (\\w+)\n\\{\n\\s+send \\w+ \\(([^\n]+)\\)");
        while ((i = rawMethod.indexIn(rawData, i)) > 0)
        {
            i += rawMethod.matchedLength();

            parsedDevice->addCommand(rawMethod.cap(1), rawMethod.cap(2));
        }

        this->AddDevice(parsedDevice);
    }
    return true;
}

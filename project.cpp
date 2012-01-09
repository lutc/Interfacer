#include <QTextStream>
#include "project.h"
#include "parser.h"

QString Project::PathToProject = "/home/marinas/MECS/projects/detsad/rootfs/";
const QString Project::m_LircdConfPath = "etc/lirc/lircd.conf";

const QString Project::ImagesDirectory = QString("/Images");
QMap<QString, Lirc *> Project::m_lircConfiges;
QMap<QString, Device*> Project::m_devices;

Project::Project()
{
}


QStringList Project::GetImages()
{
    QDir *dir = new QDir(Project::PathToProject + Project::ImagesDirectory);
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
    out.setCodec("Windows-1251");
    out << device->Save();
    file.close();
}

void Project::AddDevice(Device *device)
{
    m_devices.insert(device->GetName(), device);
}


QStringList Project::GetDevices()
{
    if (m_devices.isEmpty())
        return QStringList();

    return QStringList(m_devices.keys());
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

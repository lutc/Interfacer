#include "device.h"
#include <QDebug>

Device::Device(QString name) :
    QObject(0)
{
    name[0] = name.at(0).toUpper();
    m_name = name;
    m_caseSensitive = "false";
    m_queryPeriod = "10000";
    m_timeout = "1000";
}

QStringList Device::GetCommands()
{
    return QStringList(m_commands.keys());
}

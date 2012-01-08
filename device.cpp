#include "device.h"

Device::Device(QString name) :
    QObject(0)
{
    name[0] = name.at(0).toUpper();
    m_name = name;
}

QStringList Device::GetCommands()
{
    return QStringList(m_commands.keys());
}

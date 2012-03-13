#include "pjlinkdevice.h"

PJLinkDevice::PJLinkDevice(QString deviceName, QString ip) :
    Device(deviceName)
{
    m_ip = ip;
    addCommand("poweron", "\"%1POWR 1\" cr");
    addCommand("poweroff", "\"%1POWR 0\" cr");
    addCommand("muteon", "\"%1AVMT 31\" cr");
    addCommand("muteoff", "\"%1AVMT 30\" cr");
}

QString PJLinkDevice::Save()
{
    QString result = QString("protocol %0: tcp-ip\n" \
                             "target-ip: \"%1:%2\"\n" \
                             "query-period: %3\n" \
                             "timeout: %4\n" \
                             "case-sensitive: %5\n" \
                   "\n\n").arg(m_name).arg(m_ip).arg(DEFAULT_PORT).arg(m_queryPeriod).arg(m_timeout).arg(m_caseSensitive);
    foreach (QString commands, m_commands) {
        result += commands;
    }
    return result;
}

void PJLinkDevice::addCommand(QString commandName, QString command)
{
    QString("command %0\n" \
            "{\n" \
            "   send %1 (%2)\n" \
            "}\n\n").arg(commandName).arg(m_name).arg(command);
    m_commands.insert(commandName, command);
}

#include "pjlinkdevice.h"

const QString PJLinkDevice::DEFAULT_PORT = "4352";

PJLinkDevice::PJLinkDevice(QString deviceName, QString ip, QString port) :
    Device(deviceName)
{
    m_ip = ip;
    m_caseSensitive = "false";
    if (port.isEmpty())
        m_port = DEFAULT_PORT;
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
                   "\n\n").arg(m_name).arg(m_ip).arg(m_port).arg(m_queryPeriod).arg(m_timeout).arg(m_caseSensitive);
    foreach (QString commands, m_commands) {
        result += commands;
    }
    return result;
}



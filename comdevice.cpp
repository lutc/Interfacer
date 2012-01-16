#include "comdevice.h"

ComDevice::ComDevice(QString deviceName):
    Device(deviceName)
{
}

QString ComDevice::Save()
{
    QString result = QString("protocol %0: socket\n" \
                             "port: %1\n" \
                             "speed: %2\n" \
                             "character-size: %3\n" \
                             "parity: %4\n" \
                             "query-period: %5\n" \
                             "timeout: %6\n" \
                             "case-sensitive: %7\n" \
                   "\n\n").arg(m_name).arg(m_port).arg(m_speed).arg(m_characterSize)
            .arg(m_parity).arg(m_queryPeriod).arg(m_timeout).arg(m_caseSensitive);
    foreach (QString commands, m_commands) {
        result += commands;
    }
    return result;
}

void ComDevice::addCommand(QString commandName, QString command)
{
    QString("command %0\n" \
            "{\n" \
            "   send %1 (%2)\n" \
            "}\n\n").arg(commandName).arg(m_name).arg(command);
    m_commands.insert(commandName, command);
}

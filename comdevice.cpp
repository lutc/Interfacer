#include <QDebug>
#include "comdevice.h"

ComDevice::ComDevice(QString deviceName, QString port, QString speed, QString parity, QString characterSize):
    Device(deviceName)
{
    m_port = port;
    m_speed = speed;
    m_parity = parity;
    m_characterSize = characterSize;


}

QString ComDevice::Save()
{
    QString result = QString("protocol %0: com\n" \
                             "port: %1\n" \
                             "speed: %2\n" \
                             "character-size: %3\n" \
                             "parity: %4\n" \
                             "query-period: %5\n" \
                             "timeout: %6\n" \
                             "case-sensitive: %7\n" \
                   "\n\n").arg(m_name).arg(m_port).arg(m_speed).arg(m_characterSize)
            .arg(m_parity).arg(m_queryPeriod).arg(m_timeout).arg(m_caseSensitive);
    foreach (QString commands, m_commands.values()) {
        result += commands;
    }
    return result;
}

void ComDevice::addCommand(QString commandName, QString command)
{    
    QString commandBody = QString("command %0\n" \
            "{\n" \
            "   send %1 (%2)\n" \
            "}\n\n").arg(commandName).arg(m_name).arg(command);
    m_commands.insert(commandName, commandBody);
}

#include "lircdevice.h"

#include <QDebug>

LircDevice::LircDevice(QString name, Lirc *lirc) :
    Device(name)
{
    m_timeout = "300";
    m_queryPeriod = "10000";
    m_lirc = lirc;
    foreach (QString command, lirc->GetCommands())
    {
        addCommand(command);
    }
}

QString LircDevice::Save()
{
    QString result = QString("protocol %0: socket\n" \
                   "file: \"/var/run/lirc/lircd\"\n" \
                   "query-period: %1\n" \
                   "timeout: %2\n\n").arg(m_name).arg(m_queryPeriod).arg(m_timeout);
    foreach (QString commands, m_commands) {
        result += commands;
    }
    return result;
}

void LircDevice::addCommand(QString commandName, QString)
{
    QString command = QString(
                "command %0\n" \
                "{\n" \
                "   send %1 (\"SEND_START %2 %0\" nl)\n" \
                "   receive\n"
                "   {\n" \
                "       timeout\n" \
                "       {\n" \
                "           send %1 (\"SEND_STOP %2 %0\" nl)\n" \
                "       }\n" \
                "   }\n" \
                "}\n\n"
                ).arg(commandName).arg(m_name).arg(m_name.toLower());

    m_commands.insert(commandName, command);
}

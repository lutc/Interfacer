#include "lirc.h"
#include <QRegExp>
#include <QStringList>

#include <QDebug>

const QString Lirc::CommandSeparator = "begin remote";
Lirc::Lirc():
    m_name(""), m_isBroken(false)
{
}

bool Lirc::Parse(QString rawString)
{
    int pos = 0;
    QRegExp rxName("(name\\s+)(\\w+)");
    pos = rxName.indexIn(rawString, pos) + rxName.matchedLength();

    m_name = rxName.cap(2);
    if (m_name.isEmpty())
    {
        m_isBroken = true;
        return false;
    }
    QRegExp rxRawCodesBegin("(begin\\s+raw_codes)");
    int rawCodesPos = rxRawCodesBegin.indexIn(rawString, pos);
    if (rawCodesPos != -1)
    {
        pos = rawCodesPos;
        QRegExp rxCodeName("(name\\s+)(\\w+)");
        while ((pos = rxCodeName.indexIn(rawString, pos, QRegExp::CaretAtOffset) +
            rxCodeName.captureCount()) > rxName.pos())
            m_codes.append(rxCodeName.cap(2));
    }
    else
    {
        QRegExp rxBeginCodes("(begin\\s+codes)");
        pos = rxBeginCodes.indexIn(rawString, pos);

        QRegExp rxCodeName("(\\s)(\\w+)(\\s+)(0x[\\d\\w]+)");
        while ((pos = rxCodeName.indexIn(rawString, pos, QRegExp::CaretAtOffset) +
            rxCodeName.captureCount()) > rxName.pos())
            m_codes.append(rxCodeName.cap(2));
    }

    return true;
}

QStringList Lirc::GetCommands()
{
    QStringList list;
    foreach(QString lirc, m_codes)
        list << lirc;

    return list;
}

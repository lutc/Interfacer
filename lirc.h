#ifndef LIRC_H
#define LIRC_H

#include <QString>
#include <QVector>
class Lirc
{
public:
    Lirc();
    bool Parse(QString rawString);
    bool IsBroken(){ return m_isBroken;}
    QStringList GetCommands();
    QString Name(){return m_name;}
    const static QString CommandSeparator;
private:
    QString m_name;
    QVector<QString> m_codes;
    bool m_isBroken;
};

#endif // LIRC_H

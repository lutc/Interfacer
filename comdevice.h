#ifndef COMDEVICE_H
#define COMDEVICE_H
#include <QString>

#include "device.h"

class ComDevice : public Device
{
public:
    ComDevice(QString deviceName);
    QString Save();
    void Init();
    void addCommand(QString, QString);

private:
    QString m_port;
    QString m_speed;
    QString m_characterSize;
    QString m_parity;
    QString m_caseSensitive;
};

#endif // COMDEVICE_H

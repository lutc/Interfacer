#ifndef COMDEVICE_H
#define COMDEVICE_H
#include <QString>

#include "device.h"

class ComDevice : public Device
{
public:
    ComDevice(QString deviceName, QString port, QString speed, QString parity, QString characterSize = "8");
    QString Save();
    void Init();    

private:
    QString m_port;
    QString m_speed;
    QString m_characterSize;
    QString m_parity;
};

#endif // COMDEVICE_H

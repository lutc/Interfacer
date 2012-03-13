#ifndef PJLINKDEVICE_H
#define PJLINKDEVICE_H

#include "device.h"

class PJLinkDevice : public Device
{
    Q_OBJECT
public:
    explicit PJLinkDevice(QString deviceName, QString ip);
    QString Save();
    void addCommand(QString name, QString command);
    
signals:
    
public slots:

private:
    const static int DEFAULT_PORT = 4352;
    QString m_ip;
    QString m_caseSensitive;
    
};

#endif // PJLINKDEVICE_H

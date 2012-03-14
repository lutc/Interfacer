#ifndef PJLINKDEVICE_H
#define PJLINKDEVICE_H

#include "device.h"

class PJLinkDevice : public Device
{
    Q_OBJECT
public:    

    explicit PJLinkDevice(QString deviceName, QString ip, QString port = "");
    QString Save();    
    
signals:
    
public slots:

private:
    const static QString DEFAULT_PORT;
    QString m_ip;
    QString m_port;
    QString m_caseSensitive;
    
};

#endif // PJLINKDEVICE_H

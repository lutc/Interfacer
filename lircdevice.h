#ifndef LIRCDEVICE_H
#define LIRCDEVICE_H

#include <QStringList>

#include "device.h"
#include "lirc.h"

class LircDevice : public Device
{
    Q_OBJECT
public:
    explicit LircDevice(QString name, Lirc *lirc);
    QString Save();

signals:

public slots:

private:
    Lirc *m_lirc;
    void addCommand(QString commandName, QString = "");

};

#endif // LIRCDEVICE_H

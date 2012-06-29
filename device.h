#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include <QMap>
#include <QStringList>
#include <QGridLayout>

class Device : public QObject
{
    Q_OBJECT
public:
    explicit Device(QString name);

    virtual QString Save() = 0;
    QStringList GetCommands();
    QString GetName(){return m_name;}
    QString GetFileName(){return (m_name + "." + m_protocolName).toLower();}
    void SetProtocolName(QString protocolName){m_protocolName = protocolName;}
    virtual void addCommand(QString name, QString command = "");

signals:

public slots:

protected:
    QString m_queryPeriod;
    QString m_timeout;
    QString m_name;
    QString m_protocolName;
    QString m_caseSensitive;
    QMap<QString, QString> m_commands;    

private:


};

#endif // DEVICE_H

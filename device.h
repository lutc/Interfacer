#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include <QMap>
#include <QStringList>

class Device : public QObject
{
    Q_OBJECT
public:
    explicit Device(QString name);

    virtual QString Save() = 0;
    QStringList GetCommands();
    QString GetName(){return m_name;}
    QString GetFileName(){return (m_name + m_filenameAppendix).toLower();}
    void SetFileNameAppendix(QString appendix){m_filenameAppendix = appendix;}
signals:

public slots:

protected:
    int m_queryPeriod;
    int m_timeout;
    QString m_name;
    QString m_filenameAppendix;
    QMap<QString, QString> m_commands;

    virtual void addCommand(QString name, QString command = "") = 0;

private:


};

#endif // DEVICE_H

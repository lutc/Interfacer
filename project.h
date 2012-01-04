#ifndef PROJECT_H
#define PROJECT_H

#include <QString>
#include <QStringList>
#include <QDir>
#include <QMap>
#include "lirc.h"

class Project
{
public:
    Project();
    static QString PathToProject;
    static const QString ImagesDirectory;
    static QString LircdConfPath(){return PathToProject + m_LircdConfPath;}

    static QStringList GetImages();
    static QStringList GetLircComands(QString name);

private:
    static const QString m_LircdConfPath;
    static QMap<QString, Lirc *> m_lircConfiges;
    static void updateLircConfiges();

};

#endif // PROJECT_H

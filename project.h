#ifndef PROJECT_H
#define PROJECT_H

#include <QString>
#include <QStringList>
#include <QDir>

class Project
{
public:
    Project();
    static QString PathToProject;
    static const QString ImagesDirectory;

    static QStringList getImages();

private:

};

#endif // PROJECT_H

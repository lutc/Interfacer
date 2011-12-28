#include "project.h"
#include <QDebug>

QString Project::PathToProject = "/home/marinas/MECS/projects/detsad/rootfs/";
const QString Project::ImagesDirectory = QString("/Images");
Project::Project()
{
}


QStringList Project::getImages()
{
    QDir *dir = new QDir(Project::PathToProject + Project::ImagesDirectory);
//    dir->setFilter(QDir::NoDot | QDir::NoDotDot);
    return dir->entryList();
}

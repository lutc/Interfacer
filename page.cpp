#include "page.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>

#include "commonitemmecs.h"
#include "project.h"
#include "pageproperties.h"

#include <QDebug>
#include <QMetaProperty>
Page::Page():
    m_name("Main")
{
    int sceneHeight = 650;
    int sceneWidth = 1200;
    addRect(0, 0, sceneWidth, sceneHeight);
    for (int i = CommonItemMECS::stepOfGrid; i < sceneWidth; i += CommonItemMECS::stepOfGrid)
        addLine(i, 0, i, sceneHeight);
    for (int i = CommonItemMECS::stepOfGrid; i < sceneHeight; i += CommonItemMECS::stepOfGrid)
        addLine(0, i, sceneWidth, i);
}

void Page::drawBackground(QPainter *painter, const QRectF &)
{
    if (m_background.isEmpty())
        return;
    painter->drawImage(QPoint(0, 0), *m_backgroundImage );
}

void Page::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseDoubleClickEvent(event);
    if (selectedItems().count() > 0)
        return;
    PageProperties *properties = new PageProperties(this);
    properties->setWindowModality(Qt::ApplicationModal);
    properties->show();
}

QString Page::GetName()
{
    return m_name;
}
void Page::SetName(QString newName)
{
    qDebug() << newName;
    m_name = newName;
    emit selectionChanged();
//    emit nameChanged();
}
void Page::SetBackground(QString path)
{
    qDebug() << path;
    m_background = path;
    QString backgroundImagePath =
            Project::PathToProject + Project::ImagesDirectory
            + QString("/") + m_background;
    m_backgroundImage = new QImage(backgroundImagePath);
}

QString Page::Save()
{
    return QString("[Page]\n" \
            "Name = %0\n" \
                   "Background = Images/%1\n\n").arg(GetName()).arg(m_background);

}

void Page::Parse(QString from)
{
    QStringList list = from.split("\n", QString::SkipEmptyParts);
    list.removeFirst(); // remove element with "type"
    foreach (QString property, list){
        QStringList propertylist = property.split("=");
        this->setProperty(propertylist.at(0).trimmed().toAscii(),
                                     propertylist.at(1).trimmed());
    }
}

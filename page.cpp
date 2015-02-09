#include "page.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>

#include "commonitemmecs.h"
#include "project.h"
#include "pageproperties.h"

#include <QMetaProperty>
#ifndef QT_NO_OPENGL
#include <QtOpenGLDepends>
#include <QtWidgets/QWidget>
#include <QtOpenGLExtensions/QOpenGLExtensions>
#endif

Page::Page():
    m_name("Main")
{    
    Refresh();
}

void Page::Refresh()
{
	SCENE_HEIGHT = 900;
	SCENE_WIDTH = 1800;
	addRect(0, 0, SCENE_WIDTH, SCENE_HEIGHT);
    for (int i = CommonItemMECS::stepOfGrid; i < SCENE_WIDTH; i += CommonItemMECS::stepOfGrid)
		addLine(i, 0, i, SCENE_HEIGHT);
	for (int i = CommonItemMECS::stepOfGrid; i < SCENE_HEIGHT; i += CommonItemMECS::stepOfGrid)
		addLine(0, i, SCENE_WIDTH, i);
}

Page::Page(QString Name, QString Background)
{
    Refresh();

    SetName(Name);
    SetBackground(Background);
}

QGraphicsView *Page::GenerateGraphicsView()
{
    QGraphicsView *graphicsView = new QGraphicsView();

    graphicsView->setRenderHint(QPainter::Antialiasing, false);
    graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    graphicsView->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    #ifndef QT_NO_OPENGL
    //graphicsView->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
    #endif
    graphicsView->setRenderHint(QPainter::Antialiasing, true);
    return graphicsView;
}

void Page::drawBackground(QPainter *painter, const QRectF &)
{
	if (m_background.isEmpty())
		return;
	painter->drawImage(QRect(0, 0, SCENE_WIDTH, SCENE_HEIGHT), *m_backgroundImage);
//	QGraphicsScene::drawBackground(painter, rect);
//	painter->setBackground(QBrush(*m_backgroundImage));
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

void Page::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);
    m_newPos = event->buttonDownScenePos(Qt::RightButton);
}

void Page::UpdateBackground()
{
    SetBackground(m_background);
}

QString Page::GetName()
{
    return m_name;
}
void Page::SetName(QString newName)
{
    m_name = newName;
    emit selectionChanged();
//    emit nameChanged();
}
void Page::SetBackground(QString path)
{
	m_background = path;
    QString backgroundImagePath =
			Project::PathToProject + m_background;
    m_backgroundImage = new QImage(backgroundImagePath);
}

QString Page::Save()
{
    return QString("[Page]\n" \
            "Name = %0\n" \
				   "Background = %1\n\n").arg(GetName()).arg(m_background);

}

/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "commonitemmecs.h"

#include <QtGui>

#include "itemproperties.h"
#include "project.h"

int CommonItemMECS::stepOfGrid = 25;

CommonItemMECS::CommonItemMECS(int x, int y):
    m_width(200), m_height(50)
{
    this->x = x;
    this->y = y;
    setZValue((x + y) % 2);

    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptsHoverEvents(true);
}

QRectF CommonItemMECS::boundingRect() const
{
    return QRectF(0, 0, m_width, m_height);
}

QPainterPath CommonItemMECS::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void CommonItemMECS::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    QColor fillColor = (option->state & QStyle::State_Selected) ? color.dark(150) : color;
    if (option->state & QStyle::State_MouseOver)
        fillColor = fillColor.light(125);

    QPen oldPen = painter->pen();
    QPen pen = oldPen;
    int width = 0;
    if (option->state & QStyle::State_Selected)
        width += 2;

    pen.setWidth(width);
    pen.setColor(Qt::white);
    QBrush b = painter->brush();
    if (m_backgroundImage.isEmpty())
    {
        painter->setBrush(QBrush(fillColor.dark(option->state & QStyle::State_Sunken ? 120 : 100)));
        painter->drawRect(boundingRect());
        painter->setBrush(b);
    }
    else
    {
        QPen oldPenBorder = painter->pen();
        QPen *penBorder = new QPen(Qt::red);
        penBorder->setWidth(3);
        penBorder->setStyle(Qt::DotLine);
        painter->setPen(*penBorder);
        painter->drawRect(boundingRect());
        painter->drawImage(boundingRect().topLeft(), *m_backGroundImageCache);
        painter->setPen(oldPenBorder);
    }

    painter->setPen(pen);
    painter->drawText(boundingRect(), Qt::AlignCenter, m_text);
    painter->setPen(oldPen);

return;

}

void CommonItemMECS::setWidth(qreal width)
{
    m_width = width;
}

void CommonItemMECS::setHeight(qreal height)
{
    m_height = height;
}

void CommonItemMECS::setText(QString newText)
{
    m_text = newText;
}

void CommonItemMECS::setBackgroundImage(QString newImage)
{
    m_backgroundImage = newImage;
    if (m_backgroundImage.isEmpty())
        return;
    QString backgroundImagePath =
            Project::PathToProject + Project::ImagesDirectory
            + QString("/") + m_backgroundImage;
    m_backGroundImageCache = new QImage(backgroundImagePath);
}

qreal CommonItemMECS::getWidth()
{
    return m_width;
}

qreal CommonItemMECS::getHeight()
{
    return m_height;
}

QString CommonItemMECS::getText()
{
    return m_text;
}

QString CommonItemMECS::getBackgroundImage()
{
    return m_backgroundImage;
}

QString CommonItemMECS::Save()
{
    QString result = QString(
        "Left = %0\n" \
        "Top = %1\n" \

        "Font = Images/arial.ttf\n" \
        "FontSize = 20\n" \
        "Color = white\n").arg(scenePos().x()).arg(scenePos().y());

    /*switch (currentType)
    {
    case toglebutton:
        result = QString (
            "[TogleButton]\n"\
            "Pages = Main\n" \

            "Caption = %1\n").arg(getText()) + result +

        QString ("UpImage = Images/%0\n" \
                 "DownImage = Images/menu_light_btn.png\n" \
                 "HeldImage = Images/menu_light_btn.png\n" \

                 "OnUp  = Command Mitsubishi poweron\n" \
                 "OnDown  = Command Mitsubishi poweron\n\n")
                .arg(getBackgroundImage());
        break;
    }
*/

    return result;
}

void CommonItemMECS::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    update();
}

void CommonItemMECS::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->modifiers() & Qt::ShiftModifier) {
        stuff << event->pos();
        update();
        return;
    }
    QGraphicsItem::mouseMoveEvent(event);
}

int CommonItemMECS::snapToGrid(qreal position)
{
    int delimiter = (int)position /  stepOfGrid;
    if ((position /  stepOfGrid) - delimiter >= 0.5)
        delimiter++;
    return delimiter * stepOfGrid;
}

void CommonItemMECS::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);

    setX(snapToGrid(scenePos().x()));
    setY(snapToGrid(scenePos().y()));
    update();
}

void CommonItemMECS::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *)
{
    ItemProperties *properties = new ItemProperties(*this);
    properties->setWindowModality(Qt::ApplicationModal);
    properties->show();
}
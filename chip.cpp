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

#include "chip.h"

#include <QtGui>

#include "itemproperties.h"
#include "project.h"

int Chip::stepOfGrid = 25;

Chip::Chip(const type t, int x, int y)
    :m_width(200), m_height(50)
{
    switch (t)
    {
    case button:
        this->color = QColor(255, 0, 0);
        break;
    case toglebutton:
        this->color = QColor(0, 255, 0);
        break;
    case text:
        this->color = QColor(0, 0, 255);
        break;
    case indicator:
        this->color = QColor(200, 0, 200);
        break;
    }
    currentType = t;
    this->x = x;
    this->y = y;
    this->color = color;
    setZValue((x + y) % 2);

    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptsHoverEvents(true);
}

QRectF Chip::boundingRect() const
{
    return QRectF(0, 0, m_width, m_height);
}

QPainterPath Chip::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void Chip::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
        painter->drawImage(boundingRect(), *m_backGroundImageCache);
    }

    painter->setPen(pen);
    painter->drawText(boundingRect(), Qt::AlignCenter, m_text);
    painter->setPen(oldPen);

return;

}

Chip::type Chip::getType()
{
    return currentType;
}


void Chip::setWidth(qreal width)
{
    m_width = width;
}

void Chip::setHeight(qreal height)
{
    m_height = height;
}

void Chip::setText(QString newText)
{
    m_text = newText;
}

void Chip::setBackgroundImage(QString newImage)
{
    m_backgroundImage = newImage;
    if (m_backgroundImage.isEmpty())
        return;
    QString backgroundImagePath =
            Project::PathToProject + Project::ImagesDirectory
            + QString("/") + m_backgroundImage;
    m_backGroundImageCache = new QImage(backgroundImagePath);
}

qreal Chip::getWidth()
{
    return m_width;
}

qreal Chip::getHeight()
{
    return m_height;
}

QString Chip::getText()
{
    return m_text;
}

QString Chip::getBackgroundImage()
{
    return m_backgroundImage;
}

QString Chip::Save()
{
    QString result = QString(
    "Left = %0\n" \
    "Top = %1\n" \

    "Font = Images/arial.ttf\n" \
    "FontSize = 20\n" \
                "Color = white\n").arg(scenePos().x()).arg(scenePos().y());

    switch (currentType)
    {
    case text:
        result = QString (
            "[Text]\n"\
            "Pages = Main\n" \

            "Align = left\n") + result +
        QString ("Width = %2\nHeight = %3\nDefaultText = %4\n\n").arg(m_width).
                arg(m_height).arg(getText());
        break;

    case button:
        result = QString (
            "[Button]\n"\
            "Pages = Main\n" \

            "Caption = %1\n").arg(getText()) + result +

        QString ("UpImage = Images/%0\n" \
                 "DownImage = Images/menu_light_btn.png\n" \
                 "HeldImage = Images/menu_light_btn.png\n" \

                 "OnClick  = Command Mitsubishi poweron\n\n").arg(getBackgroundImage());
        break;
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


    return result;
}

void Chip::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    update();
}

void Chip::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->modifiers() & Qt::ShiftModifier) {
        stuff << event->pos();
        update();
        return;
    }
    QGraphicsItem::mouseMoveEvent(event);
}

int Chip::snapToGrid(qreal position)
{
    int delimiter = (int)position /  stepOfGrid;
    if ((position /  stepOfGrid) - delimiter >= 0.5)
        delimiter++;
    return delimiter * stepOfGrid;
}

void Chip::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);

    setX(snapToGrid(scenePos().x()));
    setY(snapToGrid(scenePos().y()));
    update();
}

void Chip::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *)
{
    ItemProperties *properties = new ItemProperties(*this);
    properties->setWindowModality(Qt::ApplicationModal);
    properties->show();
}

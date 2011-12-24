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

Chip::Chip(const type t, int x, int y)
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
    return QRectF(0, 0, 200, 50);
}

QPainterPath Chip::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, 200, 50);
    return path;
}

void Chip::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    QColor fillColor = (option->state & QStyle::State_Selected) ? color.dark(150) : color;
    if (option->state & QStyle::State_MouseOver)
        fillColor = fillColor.light(125);

//    const qreal lod = option->levelOfDetailFromTransform(painter->worldTransform());

    QPen oldPen = painter->pen();
    QPen pen = oldPen;
    int width = 0;
    if (option->state & QStyle::State_Selected)
        width += 2;

    pen.setWidth(width);
    QBrush b = painter->brush();
    painter->setBrush(QBrush(fillColor.dark(option->state & QStyle::State_Sunken ? 120 : 100)));

    painter->drawRect(QRect(0, 0, 200, 50));
    painter->setBrush(b);

    if (currentType == text)
    {
        painter->drawText(10, 20, "Text");
    }
return;

}

QString Chip::Save()
{
    QString result = QString(
    "Left = %0\n" \
    "Top = %1\n" \
    "Width = 200\n" \
    "Height = 50\n" \

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

        QString ("DefaultText = Projector\n\n");
        break;

    case button:
        result = QString (
            "[Button]\n"\
            "Pages = Main\n" \

            "Caption = CAPTION\n") + result +

        QString ("UpImage = Images/menu_btn.png\n" \
                 "DownImage = Images/menu_light_btn.png\n" \
                 "HeldImage = Images/menu_light_btn.png\n" \

                 "OnClick  = Command Mitsubishi poweron\n\n");
        break;
    case toglebutton:
        result = QString (
            "[TogleButton]\n"\
            "Pages = Main\n" \

            "Caption = CAPTION\n") + result +

        QString ("UpImage = Images/menu_btn.png\n" \
                 "DownImage = Images/menu_light_btn.png\n" \
                 "HeldImage = Images/menu_light_btn.png\n" \

                 "OnUp  = Command Mitsubishi poweron\n" \
                 "OnDown  = Command Mitsubishi poweron\n\n");
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

int snapToGrid(qreal position)
{
    int stepOfSnap = 50;
    int delimiter = (int)position /  stepOfSnap;
    if ((position /  stepOfSnap) - delimiter >= 0.5)
        delimiter++;
    return delimiter * stepOfSnap;
}

void Chip::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);

    setX(snapToGrid(scenePos().x()));
    setY(snapToGrid(scenePos().y()));
    update();
}

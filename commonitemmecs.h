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

#ifndef CHIP_H
#define CHIP_H

#include <QtGui/QColor>
#include <QGraphicsItem>
#include <QGridLayout>

class CommonItemMECS : public QGraphicsItem
{
public:
    enum ItemTypes{button, toglebutton, text, indicator};

    static int stepOfGrid;

    CommonItemMECS(int x, int y);

    void UpdatePosition();

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);
    virtual QString Save();

    void setWidth(qreal );
    void setHeight(qreal );
    void setText(QString );
    void setBackgroundImage(QString );
    void setPage(QString);

    qreal getWidth( );
    qreal getHeight( );
    QString getText( );
    QString getBackgroundImage( );
    QString getPage();
    bool isRemoved();
    bool isInitialized(){return m_init;}
    void setInitialized(){m_init = true;}

    virtual QString GetName() = 0;
    virtual QString GetTextName() = 0;
    virtual QGridLayout *GetPropertiesWidgets() = 0;
    virtual void AcceptWidgetsProperties() = 0;
    virtual void Copy(CommonItemMECS *);
    virtual void Parse(QString );

protected:
    QColor color;
    int m_itemFlags;

    qreal m_width;
    qreal m_height;    

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *);


private:
    int x, y;

    QList<QPointF> stuff;

    QString m_text;

    QString m_backgroundImage;
    QImage *m_backGroundImageCache;

    int snapToGrid(qreal );

    bool m_removed;
    bool m_init;
    QString m_page;
};

#endif

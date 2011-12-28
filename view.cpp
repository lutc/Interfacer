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

#include "view.h"
#include <QGraphicsItem>
#include <QtGui>
#ifndef QT_NO_OPENGL
#include <QtOpenGL>
#endif

#include <qmath.h>

#include "buttonmesc.h"
#include"textmesc.h"

View::View(QWidget *parent)
    : QFrame(parent)
{
    setFrameStyle(Sunken | StyledPanel);
    graphicsView = new QGraphicsView;
    graphicsView->setRenderHint(QPainter::Antialiasing, false);
    graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    graphicsView->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);


    // Label layout
    QHBoxLayout *labelLayout = new QHBoxLayout;

    antialiasButton = new QToolButton;
    antialiasButton->setText(tr("Antialiasing"));
    antialiasButton->setCheckable(true);
    antialiasButton->setChecked(false);
    openGlButton = new QToolButton;
    openGlButton->setText(tr("OpenGL"));
    openGlButton->setCheckable(true);


#ifndef QT_NO_OPENGL
    openGlButton->setEnabled(QGLFormat::hasOpenGL());
#else
    openGlButton->setEnabled(false);
#endif

    btnAddButton = new QToolButton;
    btnAddButton->setText("Add button");
    btnAddTogleButton = new QToolButton;
    btnAddTogleButton->setText("Add TogleButton");
    btnAddText = new QToolButton;
    btnAddText->setText("Add Text");
    btnSave = new QToolButton;
    btnSave->setText("Save");

    labelLayout->addWidget(btnAddButton);
    labelLayout->addWidget(btnAddTogleButton);
    labelLayout->addWidget(btnAddText);
    labelLayout->addStretch();
    labelLayout->addWidget(antialiasButton);
    labelLayout->addWidget(openGlButton);
    labelLayout->addWidget(btnSave);

    tabwidget = new QTabWidget;


    QGridLayout *topLayout = new QGridLayout;
    topLayout->addLayout(labelLayout, 0, 0);
    topLayout->addWidget(graphicsView, 1, 0);

    setLayout(topLayout);

    connect(antialiasButton, SIGNAL(toggled(bool)), this, SLOT(toggleAntialiasing()));
    connect(openGlButton, SIGNAL(toggled(bool)), this, SLOT(toggleOpenGL()));
    connect(btnAddButton, SIGNAL(clicked()), this, SLOT(AddButton()));
    connect(btnAddTogleButton, SIGNAL(clicked()), this, SLOT(AddTogleButton()));
    connect(btnAddText, SIGNAL(clicked()), this, SLOT(AddText()));
    connect (btnSave, SIGNAL(clicked()), ItemManager::Instance(), SLOT(SaveToFile()));

    setupMatrix();

    openGlButton->setChecked(true);
}

QGraphicsView *View::view() const
{
    return graphicsView;
}

//void View::resetView()
//{
//    zoomSlider->setValue(250);
//    rotateSlider->setValue(0);
//    setupMatrix();
//    graphicsView->ensureVisible(QRectF(0, 0, 0, 0));

//    resetButton->setEnabled(false);
//}


void View::setupMatrix()
{
//    qreal scale = qPow(qreal(2), (250 - 250) / qreal(50));

    QMatrix matrix;
//    matrix.scale(scale, scale);
//    matrix.rotate(rotateSlider->value());


    graphicsView->setMatrix(matrix);
}

void View::toggleOpenGL()
{
#ifndef QT_NO_OPENGL
    graphicsView->setViewport(openGlButton->isChecked() ? new QGLWidget(QGLFormat(QGL::SampleBuffers)) : new QWidget);
#endif
}

void View::toggleAntialiasing()
{
    graphicsView->setRenderHint(QPainter::Antialiasing, antialiasButton->isChecked());
}

void View::AddButton()
{
    AddItem(CommonItemMECS::button, 0, 0);
}

void View::AddText()
{
    AddItem(CommonItemMECS::text, 0, 0);
}

void View::AddTogleButton()
{
    AddItem(CommonItemMECS::toglebutton, 0, 0);
}

void View::AddItem(CommonItemMECS::ItemTypes type, int x, int y)
{
    QGraphicsItem *item;
    switch (type)
    {
    case CommonItemMECS::button:
        item = new ButtonMESC(x, y);
        break;

    case CommonItemMECS::text:
        item = new TextMESC(x, y);
        break;

    default:
        return;
    }

    graphicsView->scene()->addItem(item);
    ItemManager::Instance()->AddItem((CommonItemMECS*)item);
}

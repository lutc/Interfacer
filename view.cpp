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

#include "buttonmecs.h"
#include "textmesc.h"
#include "togglebuttonmecs.h"
#include "page.h"
#include "addeditdevicedialog.h"
#include "project.h"

View::View(QWidget *parent)
    : QFrame(parent)
{
    setFrameStyle(Sunken | StyledPanel);

    // Label layout
    QHBoxLayout *labelLayout = new QHBoxLayout;

    m_btnAddButton = new QToolButton;
    m_btnAddButton->setText("Add button");
    m_btnAddTogleButton = new QToolButton;
    m_btnAddTogleButton->setText("Add TogleButton");
    m_btnAddText = new QToolButton;
    m_btnAddText->setText("Add Text");
    m_btnAddPage = new QToolButton;
    m_btnAddPage->setText("Add page");
    m_btnAddDevice = new QToolButton;
    m_btnAddDevice->setText("Add Device");

    m_btnLoad = new QToolButton;
    m_btnLoad->setText("Load");
    m_btnSave = new QToolButton;
    m_btnSave->setText("Save");

    labelLayout->addWidget(m_btnAddButton);
    labelLayout->addWidget(m_btnAddTogleButton);
    labelLayout->addWidget(m_btnAddText);
    labelLayout->addSpacing(15);
    labelLayout->addWidget(m_btnAddPage);
    labelLayout->addWidget(m_btnAddDevice);
    labelLayout->addStretch();
    labelLayout->addWidget(m_btnLoad);
    labelLayout->addWidget(m_btnSave);

    m_tabWidget = new QTabWidget;
    AddPage();

    QGridLayout *topLayout = new QGridLayout;
    topLayout->addLayout(labelLayout, 0, 0);

    topLayout->addWidget(m_tabWidget, 1, 0);


    setLayout(topLayout);

    connect(m_btnAddButton, SIGNAL(clicked()), this, SLOT(AddButton()));
    connect(m_btnAddTogleButton, SIGNAL(clicked()), this, SLOT(AddTogleButton()));
    connect(m_btnAddText, SIGNAL(clicked()), this, SLOT(AddText()));
    connect(m_btnAddPage, SIGNAL(clicked()), this, SLOT(AddPage()));
    connect(m_btnSave, SIGNAL(clicked()), ItemManager::Instance(), SLOT(GenerateInterface()));
    connect(m_btnLoad, SIGNAL(clicked()), ItemManager::Instance(), SLOT(LoadFromFile()));
    connect(m_btnAddDevice, SIGNAL(clicked()), this, SLOT(AddDevice()));
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

void View::AddDevice()
{
    Device *dev = NULL;
    AddEditDeviceDialog *frmAddDevice = new AddEditDeviceDialog(dev);
    frmAddDevice->show();
}

void View::AddItem(CommonItemMECS::ItemTypes type, int x, int y)
{
    QGraphicsItem *item;
    switch (type)
    {
    case CommonItemMECS::button:
        item = new ButtonMECS(x, y);
        break;

    case CommonItemMECS::text:
        item = new TextMESC(x, y);
        break;

    case CommonItemMECS::toglebutton:
        item = new ToggleButtonMECS(x, y);
        break;

    default:
        return;
    }

    QGraphicsView *graphicsView = qobject_cast<QGraphicsView *>(m_tabWidget->currentWidget());
    graphicsView->scene()->addItem(item);
    ItemManager::Instance()->AddItem((CommonItemMECS*)item);
}

void View::AddPage()
{
    QGraphicsView *graphicsView = new QGraphicsView();
    Page *page = new Page;
    ItemManager::Instance()->AddItem(page);
    graphicsView->setScene(page);
    connect(((Page*)graphicsView->scene()), SIGNAL(selectionChanged()), this, SLOT(ChangeTabName()));

    graphicsView->setRenderHint(QPainter::Antialiasing, false);
    graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    graphicsView->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    #ifndef QT_NO_OPENGL
    graphicsView->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
    #endif
    graphicsView->setRenderHint(QPainter::Antialiasing, true);

    m_tabWidget->setUpdatesEnabled(false);
    m_tabWidget->addTab(graphicsView, "Main");

    m_tabWidget->setUpdatesEnabled(true);
}

void View::ChangeTabName()
{
    m_tabWidget->setTabText(m_tabWidget->currentIndex(),
                          ((Page *)qobject_cast<QGraphicsView *>(m_tabWidget->currentWidget())->scene())->GetName());
}

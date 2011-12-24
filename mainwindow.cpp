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

#include "mainwindow.h"
#include "view.h"
#include "chip.h"

#include <QtGui>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    populateScene();


    View *view = new View();

    view->view()->setScene(scene);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(view);
    setLayout(layout);

    setWindowTitle(tr("Interfacer"));
}

void MainWindow::populateScene()
{
    scene = new QGraphicsScene;
    int sceneHeight = 700;
    int sceneWidth = 1200;
    scene->addRect(0, 0, sceneWidth, sceneHeight);
    for (int i = 50; i < sceneWidth; i += 50)
        scene->addLine(i, 0, i, sceneHeight);
    for (int i = 50; i < sceneHeight; i += 50)
        scene->addLine(0, i, sceneWidth, i);
return;
//    QImage image(":/qt4logo.png");

    // Populate scene
    int xx = 0;
    int nitems = 0;
    for (int i = -11000; i < 11000; i += 110) {
        ++xx;
        int yy = 0;
        for (int j = -7000; j < 7000; j += 70) {
            ++yy;
//            qreal x = (i + 11000) / 22000.0;
//            qreal y = (j + 7000) / 14000.0;

//            QColor color(image.pixel(int(image.width() * x), int(image.height() * y)));
//            QGraphicsItem *item = new Chip(color, xx, yy);
//            item->setPos(QPointF(i, j));
//            scene->addItem(item);

            ++nitems;
        }
    }
}

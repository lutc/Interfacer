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
#include <QtGui>

#include "view.h"
#include "project.h"
#include "commonitemmecs.h"
#include "parser.h"
#include "lirc.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    View *view = new View();

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(view);
    setLayout(layout);

    setWindowTitle(tr("Interfacer"));
//    Project::GetLircComands("lifesize");

//    QString dir = QFileDialog::getExistingDirectory(this, tr("Select Project Directory"),
//                                                    "/home/marinas/MECS/projects/detsad/rootfs/",
//                                                    QFileDialog::ShowDirsOnly
//                                                    | QFileDialog::DontResolveSymlinks);

//    if (dir.length() > 0)
//        Project::PathToProject = dir;
}



RESOURCES += images.qrc

HEADERS += mainwindow.h view.h chip.h \
    itemmanager.h
SOURCES += main.cpp \
    itemmanager.cpp
SOURCES += mainwindow.cpp view.cpp chip.cpp

contains(QT_CONFIG, opengl):QT += opengl

build_all:!build_pass {
    CONFIG -= build_all
    CONFIG += release
}

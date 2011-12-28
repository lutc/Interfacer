RESOURCES += images.qrc

HEADERS += mainwindow.h view.h \
    itemmanager.h \
    itemproperties.h \
    project.h \
    buttonmesc.h \
    commonitemmecs.h \
    textmesc.h
SOURCES += main.cpp \
    itemmanager.cpp \
    itemproperties.cpp \
    project.cpp \
    buttonmesc.cpp \
    commonitemmecs.cpp \
    textmesc.cpp
SOURCES += mainwindow.cpp view.cpp

contains(QT_CONFIG, opengl):QT += opengl

build_all:!build_pass {
    CONFIG -= build_all
    CONFIG += release
}

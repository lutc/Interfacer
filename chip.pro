RESOURCES += images.qrc

HEADERS += mainwindow.h view.h \
    itemmanager.h \
    itemproperties.h \
    project.h \
    commonitemmecs.h \
    textmesc.h \
    togglebuttonmecs.h \
    buttonmecs.h \
    itemaction.h
SOURCES += main.cpp \
    itemmanager.cpp \
    itemproperties.cpp \
    project.cpp \
    commonitemmecs.cpp \
    textmesc.cpp \
    togglebuttonmecs.cpp \
    buttonmecs.cpp \
    itemaction.cpp
SOURCES += mainwindow.cpp view.cpp

contains(QT_CONFIG, opengl):QT += opengl

build_all:!build_pass {
    CONFIG -= build_all
    CONFIG += release
}

RESOURCES += images.qrc

HEADERS += mainwindow.h view.h \
    itemmanager.h \
    project.h \
    commonitemmecs.h \
    textmesc.h \
    togglebuttonmecs.h \
    buttonmecs.h \
    itemaction.h \
    interfaceitemproperties.h \
    parser.h \
    page.h \
    pageproperties.h \
    lirc.h \
    device.h \
    lircdevice.h \
    addeditdevicedialog.h \
    comdevice.h \
    pjlinkdevice.h \
    addmethoddialog.h
SOURCES += main.cpp \
    itemmanager.cpp \
    project.cpp \
    commonitemmecs.cpp \
    textmesc.cpp \
    togglebuttonmecs.cpp \
    buttonmecs.cpp \
    itemaction.cpp \
    interfaceitemproperties.cpp \
    parser.cpp \
    page.cpp \
    pageproperties.cpp \
    lirc.cpp \
    device.cpp \
    lircdevice.cpp \
    addeditdevicedialog.cpp \
    comdevice.cpp \
    pjlinkdevice.cpp \
    addmethoddialog.cpp
SOURCES += mainwindow.cpp view.cpp

contains(QT_CONFIG, opengl):QT += opengl

build_all:!build_pass {
    CONFIG -= build_all
    CONFIG += release
}

FORMS += \
    addeditdevicedialog.ui \
    addmethoddialog.ui

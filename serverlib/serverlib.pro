TEMPLATE = lib
TARGET = barbelserver

QT = core network

CONFIG += staticlib

MOC_DIR = .moc
OBJECTS_DIR = .obj

INCLUDEPATH += src include/Barbel

HEADERS += \
    src/clientconnection.h \
    src/scene.h \
    include/Barbel/servermanager.h

SOURCES += \
    src/clientconnection.cpp \
    src/scene.cpp \
    src/servermanager.cpp


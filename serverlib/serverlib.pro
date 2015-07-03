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
    include/Barbel/servermanager.h \
    src/object.h \
    src/player.h

SOURCES += \
    src/clientconnection.cpp \
    src/scene.cpp \
    src/servermanager.cpp \
    src/object.cpp \
    src/player.cpp


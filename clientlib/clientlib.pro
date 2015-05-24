TEMPLATE = lib
TARGET = barbelclient

QT = core network

CONFIG += staticlib

MOC_DIR = .moc
OBJECTS_DIR = .obj

INCLUDEPATH += src include/Barbel

HEADERS += \
    include/Barbel/clientmanager.h

SOURCES += \
    src/clientmanager.cpp

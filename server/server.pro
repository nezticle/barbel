TEMPLATE = app
TARGET = barbel-server

QT += network

INCLUDEPATH += ../serverlib/include
DEPENDPATH += ../serverlib/include

LIBS += -lbarbelserver

win32 {
    CONFIG(debug, debug|release) {
        LIBS += -L../serverlib/debug
    } else {
        LIBS += -L../serverlib/release
    }
} else {
    LIBS += -L../serverlib/
}

# Default rules for deployment.
include(../deployment.pri)

SOURCES += \
    main.cpp

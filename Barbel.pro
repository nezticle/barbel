TEMPLATE = app

QT += qml quick gamepad 3dcore 3drenderer

SOURCES += src/main.cpp \
    src/scene.cpp \
    src/sceneviewitem.cpp

RESOURCES += qml/qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    src/scene.h \
    src/sceneviewitem.h

TEMPLATE = app

QT += qml quick widgets dbus

SOURCES += main.cpp \
    a2dpsource.cpp \
    settings.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    a2dpsource.h \
    settings.h
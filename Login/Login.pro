TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    storebrowse.cpp \
    loginbox.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = /home/daniel/Login

# Default rules for deployment.
include(deployment.pri)

DISTFILES +=

HEADERS += \
    storebrowse.h \
    loginbox.h

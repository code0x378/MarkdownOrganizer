include(../../defaults.pri)

TARGET = $$qtLibraryTarget(coreplugin)
DESTDIR += $$PWD/../../../dist/dist-apps/plugins
TEMPLATE = lib
CONFIG += plugin

QT += widgets testlib

CONFIG += c++17

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../mdocore/release/ -lmdocore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../mdocore/debug/ -lmdocore
else:unix: LIBS += -L$$OUT_PWD/../../mdocore/ -lmdocore

INCLUDEPATH += $$PWD/../../mdocore
DEPENDPATH += $$PWD/../../mdocore

HEADERS += \
    src/coreplugin/coreplugin.h

SOURCES += \
    src/coreplugin/coreplugin.cpp

include(../../defaults.pri)

TARGET = $$qtLibraryTarget(staticaplugin)
DESTDIR += $$PWD/../../../dist/dist-apps/plugins
TEMPLATE = lib
CONFIG += plugin

ParentDirectory =  $$PWD/../../../build/staticaplugin
release: $$ParentDirectory
debug:   $$ParentDirectory
RCC_DIR = $$ParentDirectory
UI_DIR = $$ParentDirectory
MOC_DIR = $$ParentDirectory
OBJECTS_DIR = $$ParentDirectory
LIBS += -L$$PWD/../../../build/markdownorganizer -lmdocore

QT += widgets testlib

CONFIG += c++17
HEADERS += src/staticaplugin/staticaplugin.h
SOURCES += src/staticaplugin/staticaplugin.cpp
RESOURCES +=
INCLUDEPATH += ../../app/src/

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../mdocore/release/ -lmdocore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../mdocore/debug/ -lmdocore
else:unix: LIBS += -L$$OUT_PWD/../../mdocore/ -lmdocore

INCLUDEPATH += $$PWD/../../mdocore
DEPENDPATH += $$PWD/../../mdocore

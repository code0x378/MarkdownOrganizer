include(../../defaults.pri)

TARGET = $$qtLibraryTarget(middlemanplugin)
DESTDIR += $$PWD/../../../dist/dist-apps/plugins
TEMPLATE = lib
CONFIG += plugin

ParentDirectory =  $$PWD/../../../build/middlemanplugin
release: $$ParentDirectory
debug:   $$ParentDirectory
RCC_DIR = $$ParentDirectory
UI_DIR = $$ParentDirectory
MOC_DIR = $$ParentDirectory
OBJECTS_DIR = $$ParentDirectory
LIBS += -L$$PWD/../../../build/markdownorganizer -lmdocore

QT += widgets printsupport testlib
HEADERS += src/middlemanplugin/middlemanplugin.h
SOURCES += src/middlemanplugin/middlemanplugin.cpp
RESOURCES +=
INCLUDEPATH += ../../app/src/

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../mdocore/release/ -lmdocore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../mdocore/debug/ -lmdocore
else:unix: LIBS += -L$$OUT_PWD/../../mdocore/ -lmdocore

INCLUDEPATH += $$PWD/../../mdocore
DEPENDPATH += $$PWD/../../mdocore


QT += core gui network widgets sql

CONFIG += c++17

TARGET = mdocore
TEMPLATE = lib
INCLUDEPATH += src
DEFINES += GFCORE_LIBRARY

CONFIG += static

INSTALLS += \
    install_it\

RESOURCES += \
    resources/mdocore.qrc

HEADERS += \
    src/mdocore/gui/docks/dockdata.h \
    src/mdocore/util/qtutils.h \
    src/mdocore/mdocore_global.h \
    src/mdocore/global.h \
    src/mdocore/iplugin.h \
    src/mdocore/logmanager.h \
    src/mdocore/objectmanager.h \
    src/mdocore/plugindata.h \
    src/mdocore/pluginmanager.h \
    src/mdocore/settingsmanager.h \
    src/mdocore/mdocore_global.h \
    src/mdocore/gui/docks/dockdata.h \
    src/mdocore/gui/docks/dockdata.h \
    src/mdocore/util/qtutilcs.h \
    src/mdocore/mdocore_global.h \
    src/mdocore/global.h \
    src/mdocore/iplugin.h \
    src/mdocore/logmanager.h \
    src/mdocore/objectmanager.h \
    src/mdocore/pluginmanager.h \
    src/mdocore/settingsmanager.h \
    src/mdocore/gui/dialogs/aboutdialog.h \
    src/mdocore/gui/docks/dockdata.h \
    src/mdocore/gui/dialogs/plugindialog.h \
    src/mdocore/settingsmanager.h \
    src/mdocore/gui/dialogs/settingsdialog.h \
    src/mdocore/slugify.hpp \
    src/mdocore/plugindata.h \
    src/mdocore/mdoapplication.h \
    src/mdocore/lib/qt-mustache/mustache.h \
    src/mdocore/lib/hoedown/src/autolink.h \
    src/mdocore/lib/hoedown/src/buffer.h \
    src/mdocore/lib/hoedown/src/document.h \
    src/mdocore/lib/hoedown/src/escape.h \
    src/mdocore/lib/hoedown/src/html.h \
    src/mdocore/lib/hoedown/src/stack.h \
    src/mdocore/lib/hoedown/src/version.h \
    src/mdocore/lib/hoedown/bin/common.h \
    src/mdocore/lib/hoedown/src/autolink.h \
    src/mdocore/lib/hoedown/src/buffer.h \
    src/mdocore/lib/hoedown/src/document.h \
    src/mdocore/lib/hoedown/src/escape.h \
    src/mdocore/lib/hoedown/src/html.h \
    src/mdocore/lib/hoedown/src/stack.h \
    src/mdocore/lib/hoedown/src/version.h \
    src/mdocore/lib/qt-mustache/mustache.h \
    src/mdocore/lib/QtAwesome/QtAwesome/QtAwesome.h \
    src/mdocore/lib/QtAwesome/QtAwesome/QtAwesomeAnim.h \
    src/mdocore/models/resource.h \
    src/mdocore/models/blogresource.h \
    src/mdocore/models/pageresource.h \
    src/mdocore/models/model.h \
    src/mdocore/models/project.h \
    src/mdocore/databasemanager.h \
    src/mdocore/db/initdb.h \
    src/mdocore/gui/dialogs/projectdialog.h \
    src/mdocore/lib/hoedown/bin/common.h \
    src/mdocore/lib/hoedown/src/autolink.h \
    src/mdocore/lib/hoedown/src/buffer.h \
    src/mdocore/lib/hoedown/src/document.h \
    src/mdocore/lib/hoedown/src/escape.h \
    src/mdocore/lib/hoedown/src/html.h \
    src/mdocore/lib/hoedown/src/stack.h \
    src/mdocore/lib/hoedown/src/version.h \
    src/mdocore/lib/qt-mustache/mustache.h \
    src/mdocore/lib/QtAwesome/QtAwesome/QtAwesome.h \
    src/mdocore/lib/QtAwesome/QtAwesome/QtAwesomeAnim.h \
    src/mdocore/gui/dialogs/projecttablemodel.h

SOURCES += \
    src/mdocore/util/qtutils.cpp \
    src/mdocore/logmanager.cpp \
    src/mdocore/objectmanager.cpp \
    src/mdocore/plugindata.cpp \
    src/mdocore/pluginmanager.cpp \
    src/mdocore/settingsmanager.cpp \
    src/mdocore/util/qtutils.cpp \
    src/mdocore/logmanager.cpp \
    src/mdocore/objectmanager.cpp \
    src/mdocore/pluginmanager.cpp \
    src/mdocore/settingsmanager.cpp \
    src/mdocore/gui/dialogs/aboutdialog.cpp \
    src/mdocore/gui/dialogs/plugindialog.cpp \
    src/mdocore/gui/dialogs/settingsdialog.cpp \
    src/mdocore/plugindata.cpp \
    src/mdocore/mdoapplication.cpp \
    src/mdocore/lib/qt-mustache/mustache.cpp \
    src/mdocore/lib/hoedown/src/autolink.c \
    src/mdocore/lib/hoedown/src/buffer.c \
    src/mdocore/lib/hoedown/src/document.c \
    src/mdocore/lib/hoedown/src/escape.c \
    src/mdocore/lib/hoedown/src/html_blocks.c \
    src/mdocore/lib/hoedown/src/html_smartypants.c \
    src/mdocore/lib/hoedown/src/html.c \
    src/mdocore/lib/hoedown/src/stack.c \
    src/mdocore/lib/hoedown/src/version.c \
    src/mdocore/lib/qt-mustache/mustache.cpp \
    src/mdocore/lib/QtAwesome/QtAwesome/QtAwesome.cpp \
    src/mdocore/lib/QtAwesome/QtAwesome/QtAwesomeAnim.cpp \
    src/mdocore/lib/QtAwesome/QtAwesomeSample/main.cpp \
    src/mdocore/lib/hoedown/bin/hoedown.c \
    src/mdocore/lib/hoedown/bin/smartypants.c \
    src/mdocore/lib/hoedown/src/autolink.c \
    src/mdocore/lib/hoedown/src/buffer.c \
    src/mdocore/lib/hoedown/src/document.c \
    src/mdocore/lib/hoedown/src/escape.c \
    src/mdocore/lib/hoedown/src/html.c \
    src/mdocore/lib/hoedown/src/html_blocks.c \
    src/mdocore/lib/hoedown/src/html_smartypants.c \
    src/mdocore/lib/hoedown/src/stack.c \
    src/mdocore/lib/hoedown/src/version.c \
    src/mdocore/models/resource.cpp \
    src/mdocore/models/blogresource.cpp \
    src/mdocore/models/pageresource.cpp \
    src/mdocore/models/model.cpp \
    src/mdocore/models/project.cpp \
    src/mdocore/databasemanager.cpp \
    src/mdocore/gui/dialogs/projectdialog.cpp \
    src/mdocore/lib/qt-mustache/mustache.cpp \
    src/mdocore/lib/QtAwesome/QtAwesome/QtAwesome.cpp \
    src/mdocore/lib/QtAwesome/QtAwesome/QtAwesomeAnim.cpp \
    src/mdocore/lib/QtAwesome/QtAwesomeSample/main.cpp \
    src/mdocore/lib/hoedown/bin/hoedown.c \
    src/mdocore/lib/hoedown/bin/smartypants.c \
    src/mdocore/lib/hoedown/src/autolink.c \
    src/mdocore/lib/hoedown/src/buffer.c \
    src/mdocore/lib/hoedown/src/document.c \
    src/mdocore/lib/hoedown/src/escape.c \
    src/mdocore/lib/hoedown/src/html.c \
    src/mdocore/lib/hoedown/src/html_blocks.c \
    src/mdocore/lib/hoedown/src/html_smartypants.c \
    src/mdocore/lib/hoedown/src/stack.c \
    src/mdocore/lib/hoedown/src/version.c \
    src/mdocore/gui/dialogs/projecttablemodel.cpp

FORMS += \
    src/mdocore/gui/dialogs/aboutdialog.ui \
    src/mdocore/gui/dialogs/plugindialog.ui \
    src/mdocore/gui/dialogs/settingsdialog.ui \
    src/mdocore/gui/dialogs/projectdialog.ui

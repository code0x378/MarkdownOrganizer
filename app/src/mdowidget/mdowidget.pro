include(../defaults.pri)

QT += core gui network widgets printsupport help opengl qml quick quickwidgets
TEMPLATE = app
INCLUDEPATH += src
DESTDIR += $$PWD/../../dist/dist-apps

ParentDirectory =  $$PWD/../../build/markdownorganizer
release: $$ParentDirectory
debug:   $$ParentDirectory
RCC_DIR = $$ParentDirectory
UI_DIR = $$ParentDirectory
MOC_DIR = $$ParentDirectory
OBJECTS_DIR = $$ParentDirectory
QMAKE_LIBDIR += $$ParentDirectory

SOURCES += \
    src/mdowidget/gui/widgetmainwindow.cpp \
    src/mdowidget/widget-main.cpp

HEADERS += \
    src/mdowidget/gui/widgetmainwindow.h

FORMS += \
    src/mdowidget/gui/widgetmainwindow.ui

RESOURCES += \
    	resources/mdowidget.qrc

win32 {
    TARGET = "MarkdownOrganizerWidget.exe"
}
macx {
    TARGET = "MarkdownOrganizerWidget"
}
linux {
    TARGET = "MarkdownOrganizerWidget"
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../mdocore/release/ -lmdocore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../mdocore/debug/ -lmdocore
else:unix: LIBS += -L$$OUT_PWD/../mdocore/ -lmdocore

INCLUDEPATH += $$PWD/../mdocore
DEPENDPATH += $$PWD/../mdocore

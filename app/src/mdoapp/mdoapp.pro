include(../defaults.pri)

TARGET = "Markdown Organizer"
QT += core gui network widgets printsupport help webenginewidgets
TEMPLATE = app
INCLUDEPATH += src
DESTDIR += $$PWD/../../dist/dist-apps
HEADERS += \
    src/mdoapp/gui/browserwindow.h \
    src/mdoapp/gui/appmainwindow.h \
    src/mdoapp/gui/docks/dockdata.h \
    src/mdoapp/gui/docks/mdodockwidget.h \
    src/mdoapp/gui/docks/helpdockwidget.h \
    src/mdoapp/gui/docks/logdockwidget.h \
    src/mdoapp/gui/docks/menudockwidget.h \
    src/mdoapp/gui/tools/editortoolwidget.h \
    src/mdoapp/gui/tools/dashboardtoolwidget.h \
    src/mdoapp/gui/tools/historytoolwidget.h \
    src/mdoapp/gui/tools/helptoolwidget.h \
    src/mdoapp/gui/docks/projectdockwidget.h \
    src/mdoapp/gui/widgets/helpwidget.h \
    src/mdoapp/gui/helpwindow.h \
    src/mdoapp/gui/widgets/projectwidget.h \
    src/mdoapp/gui/docks/previewdockwidget.h

SOURCES += \
    src/mdoapp/gui/browserwindow.cpp \
    src/mdoapp/gui/appmainwindow.cpp \
    src/mdoapp/app-main.cpp \
    src/mdoapp/gui/docks/dockdata.cpp \
    src/mdoapp/gui/docks/mdodockwidget.cpp \
    src/mdoapp/gui/docks/helpdockwidget.cpp \
    src/mdoapp/gui/docks/logdockwidget.cpp \
    src/mdoapp/gui/docks/menudockwidget.cpp \
    src/mdoapp/gui/tools/editortoolwidget.cpp \
    src/mdoapp/gui/tools/dashboardtoolwidget.cpp \
    src/mdoapp/gui/tools/historytoolwidget.cpp \
    src/mdoapp/gui/tools/helptoolwidget.cpp \
    src/mdoapp/gui/docks/projectdockwidget.cpp \
    src/mdoapp/gui/widgets/helpwidget.cpp \
    src/mdoapp/gui/helpwindow.cpp \
    src/mdoapp/gui/widgets/projectwidget.cpp \
    src/mdoapp/gui/docks/previewdockwidget.cpp

FORMS += \
    src/mdoapp/gui/appmainwindow.ui \
    src/mdoapp/gui/browserwindow.ui \
    src/mdoapp/gui/docks/helpdockwidget.ui \
    src/mdoapp/gui/docks/logdockwidget.ui \
    src/mdoapp/gui/docks/menudockwidget.ui \
    src/mdoapp/gui/tools/editortoolwidget.ui \
    src/mdoapp/gui/tools/dashboardtoolwidget.ui \
    src/mdoapp/gui/tools/historytoolwidget.ui \
    src/mdoapp/gui/tools/helptoolwidget.ui \
    src/mdoapp/gui/docks/projectdockwidget.ui \
    src/mdoapp/gui/widgets/helpwidget.ui \
    src/mdoapp/gui/helpwindow.ui \
    src/mdoapp/gui/widgets/projectwidget.ui \
    src/mdoapp/gui/docks/previewdockwidget.ui

OTHER_FILES +=

RESOURCES += \
    resources/mdoapp.qrc


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../mdocore/release/ -lmdocore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../mdocore/debug/ -lmdocore
else:unix: LIBS += -L$$OUT_PWD/../mdocore/ -lmdocore

INCLUDEPATH += $$PWD/../mdocore
DEPENDPATH += $$PWD/../mdocore

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../lib/SmtpClient/release/ -lSmtpClient
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../lib/SmtpClient/debug/ -lSmtpClient
else:unix: LIBS += -L$$OUT_PWD/../lib/SmtpClient/ -lSmtpClient

INCLUDEPATH += $$PWD/../lib/SmtpClient
DEPENDPATH += $$PWD/../lib/SmtpClient


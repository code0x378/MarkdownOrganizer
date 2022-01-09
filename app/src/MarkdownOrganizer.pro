TEMPLATE = subdirs
CONFIG+=ordered c++11
SUBDIRS = \
    lib/SmtpClient \
    mdocore \
    mdoapp \
    mdoplugins \
    mdowidget \
    mdomobile

mdoapp.depends = SmtpClient
mdoapp.depends = mdocore
mdowidget.depends = mdocore
mdoplugins.depends = mdocore
mobile.depends = mdocore

RESOURCES += \
    mdocore/resources/mdocore.qrc

TRANSLATIONS += \
    mdocore/resources/mdocore/lang/mdo_en.ts

win32 {
    PWD_WIN = $${PWD}
    DESTDIR_WIN = $${OUT_PWD}
    PWD_WIN ~= s,/,\\,g
    DESTDIR_WIN ~= s,/,\\,g
    copydata.commands = $$quote(cmd /c xcopy /S /I /Y $${PWD_WIN}\\resources $${DESTDIR_WIN})\\..\\dist\\dist-apps\\resources
}
macx {
    copydata.commands = $(COPY_DIR) $$PWD/resources $$PWD/../dist/dist-apps/MarkdownOrganizer.app/Contents/MacOS/
#    copydata.commands = $(COPY_DIR) $$PWD/resources $$PWD/../dist/dist-apps
}
linux {
    copydata.commands = $(COPY_DIR) $$PWD/resources $$PWD/../dist/dist-apps
}

first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata

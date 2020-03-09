include(../defaults.pri)

TEMPLATE = subdirs
CONFIG+=ordered
SUBDIRS = \
    mdoplugin \
    coreplugin \
    hugoplugin \
    staticaplugin \
    middlemanplugin

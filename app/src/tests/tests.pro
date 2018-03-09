include(../defaults.pri)
TEMPLATE = app

CONFIG   += console
CONFIG   -= app_bundle
CONFIG   -= qt

SOURCES += main.cpp

LIBS += -lunittest++ -L../src -liqcore
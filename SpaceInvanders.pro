TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt


INCLUDEPATH += $$PWD/SDL2-2.0.9/i686-w64-mingw32/include/SDL2

LIBS += -L$$PWD/SDL2-2.0.9/i686-w64-mingw32/lib

LIBS += -lSDL2

DEFINES += SLD_MAIN_HANDLED

SOURCES +=
SOURCES += \
        client.c


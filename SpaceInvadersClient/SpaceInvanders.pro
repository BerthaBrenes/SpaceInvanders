TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lws2_32
LIBS += -lMswsock
LIBS += -lAdvApi32

INCLUDEPATH += $$PWD/SDL2-2.0.9/i686-w64-mingw32/include/SDL2
LIBS += -L$$PWD/SDL2-2.0.9/i686-w64-mingw32/lib
LIBS += -lSDL2


INCLUDEPATH += $$PWD/SDL2_image-2.0.4/i686-w64-mingw32/include/SDL2
LIBS += -L$$PWD/SDL2_image-2.0.4/i686-w64-mingw32/lib
LIBS += -lSDL2_image


DEFINES += SLD_MAIN_HANDLED

SOURCES += \
        src/main.c
SOURCES += \
        src/draw.c
SOURCES += \
        src/client.c
SOURCES += \
        src/init.c
SOURCES += \
        src/input.c

SOURCES +=
HEADERS += \
        src/draw.h
HEADERS += \
        src/common.h
HEADERS += \
        src/init.h
HEADERS += \
        src/input.h
HEADERS += \
        src/main.h
HEADERS += \
        src/structs.h
HEADERS += \
        src/defs.h

HEADERS += \
    src/client.h

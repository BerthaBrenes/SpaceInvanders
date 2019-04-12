TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.c

HEADERS += \
    qsocket.h

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += json-c

DISTFILES += \
    data.json \
    test.txt

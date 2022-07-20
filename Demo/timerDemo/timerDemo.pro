TEMPLATE = app
CONFIG += console c++20
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        timer.cpp

HEADERS += \
    timer.h
unix|win32: LIBS += -lpthread

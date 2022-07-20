TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lmariadbcpp
unix|win32: LIBS += -lpthread


SOURCES += \
        cache.cpp \
        comment.cpp \
        commentbroker.cpp \
        commentproxy.cpp \
        main.cpp \
        messagesequence.cpp \
        mytimer.cpp \
        netizen.cpp \
        netizenbroker.cpp \
        netizenproxy.cpp \
        publishvideonotification.cpp \
        relationalbroker.cpp \
        video.cpp \
        videobroker.cpp \
        videofile.cpp \
        videofilebroker.cpp \
        videofileproxy.cpp \
        videoproxy.cpp \
        videosocialcontrol.cpp

HEADERS += \
    cache.h \
    comment.h \
    commentbroker.h \
    commentinterface.h \
    commentproxy.h \
    json.hpp \
    messagesequence.h \
    mytimer.h \
    netizen.h \
    netizenbroker.h \
    netizeninterface.h \
    netizenproxy.h \
    publishvideonotification.h \
    relationalbroker.h \
    video.h \
    videobroker.h \
    videofile.h \
    videofilebroker.h \
    videofileinterface.h \
    videofileproxy.h \
    videointerface.h \
    videoproxy.h \
    videosocialcontrol.h

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        PYS.cpp \
        judge.cpp

HEADERS += \
        ../sw_academy_utils/avgtree.h \
        judge.h

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += WYB.cpp \
          judge.cpp

HEADERS += judge.h


copydata.commands = $(COPY_DIR) $$PWD/res $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata

DISTFILES += \
  res/WYB0a.in \
  res/WYB0a.out \
  res/WYB0b.in \
  res/WYB0b.out

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KanoTest
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
           qmainwidget.cpp \
           stepwidgetitem.cpp

HEADERS  += qmainwidget.h \
            stepwidgetitem.h \
            lib/Challenge.h \
            lib/json.hpp

FORMS    += qmainwidget.ui \
            stepwidgetitem.ui

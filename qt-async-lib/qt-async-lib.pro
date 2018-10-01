CONFIG += staticlib
CONFIG += c++14

TARGET = qt-async-lib
TEMPLATE = lib
VERSION = 1.0.0

QT       += widgets concurrent
QT       -= gui

SOURCES += \
    values/AsyncValueBase.cpp \
    widgets/AsyncWidgetProxy.cpp \
    widgets/AsyncWidgetError.cpp \
    third_party/QtWaitingSpinner/waitingspinnerwidget.cpp \
    widgets/AsyncWidgetProgressBar.cpp \
    widgets/AsyncWidgetProgressSpinner.cpp

HEADERS += \
    values/AsyncValueBase.h \
    values/AsyncValueTemplate.h \
    values/AsyncError.h \
    values/AsyncProgress.h \
    values/AsyncValue.h \
    widgets/AsyncWidgetProxy.h \
    widgets/AsyncWidgetBase.h \
    widgets/AsyncWidget.h \
    widgets/AsyncWidgetError.h \
    third_party/QtWaitingSpinner/waitingspinnerwidget.h \
    Config.h \
    widgets/AsyncWidgetProgressBar.h \
    widgets/AsyncWidgetProgressSpinner.h \
    values/AsyncValueRun.h \
    third_party/scope_exit.h
	
DEFINES += QT_DEPRECATED_WARNINGS

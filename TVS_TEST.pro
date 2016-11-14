#-------------------------------------------------
#
# Project created by QtCreator 2016-06-24T12:04:56
#
#-------------------------------------------------

QT += core gui
QT += charts
QT += serialport
QT += sql


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TVS_TEST
TEMPLATE = app


SOURCES += main.cpp\
		mainwindow.cpp \
	rigol_ds1102e.cpp \
	tvs_tester.cpp \
	settings_and_data.cpp \
    chart.cpp

HEADERS  += mainwindow.h \
	rigol_ds1102e.h \
	tvs_tester.h \
	visa/visa.h \
	visa/visatype.h \
	visa/vpptype.h \
	settings_and_data.h \
    chart.h

FORMS    += mainwindow.ui \
	settings_and_data.ui


win32: LIBS += -L$$PWD/./ -lvisa32

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

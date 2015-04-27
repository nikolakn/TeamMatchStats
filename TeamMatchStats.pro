#-------------------------------------------------
#
# Project created by QtCreator 2015-03-05T15:54:24
#
#-------------------------------------------------

QT += core gui network
DEFINES += QT_NO_SSL
QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
    QT += webkitwidgets
} else {
    QT += webkit
}
TARGET = TeamMatchStats
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    nkweb.cpp \
    nkmecevi.cpp \
    nkgames.cpp \
    dialog2.cpp \
    unosmecadialog.cpp \
    nktimedialog.cpp \
    nkgamest.cpp \
    nktabla.cpp

HEADERS  += mainwindow.h \
    nkweb.h \
    nkmecevi.h \
    nkgames.h \
    TableItem.h \
    TableItemDouble.h \
    dialog2.h \
    unosmecadialog.h \
    nktimedialog.h \
    nkgamest.h \
    nktabla.h

FORMS    += mainwindow.ui \
    dialog.ui \
    dialog2.ui \
    unosmecadialog.ui \
    nktimedialog.ui

QT  += core gui
QT  += network sql

TARGET = graphicPlottin
TEMPLATE = app

HEADERS += \
    mychart1.h \
    mainwindow.h \
    listenthread.h \
    login.h \
    mygauge2.h \
    mygauge1.h \
    databasemanager.h \
    timeselect.h \
    plotter.h \
    insertthread.h

SOURCES += \
    mychart1.cpp \
    main.cpp \
    mainwindow.cpp \
    listenthread.cpp \
    login.cpp \
    mygauge2.cpp \
    mygauge1.cpp \
    databasemanager.cpp \
    timeselect.cpp \
    plotter.cpp \
    insertthread.cpp

FORMS += \
    mainwindow.ui \
    login.ui \
    timeselect.ui

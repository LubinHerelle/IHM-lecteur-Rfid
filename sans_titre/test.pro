LIBS += -L/path/to/library -luFCoder
LIBS += -LC:/Libraries/uFCoder -luFCoder
INCLUDEPATH += C:/Libraries/uFCoder/include

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BadgeReader
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    badgereaderthread.cpp

HEADERS += \
    mainwindow.h \
    badgereaderthread.h

FORMS += \
    mainwindow.ui

# Ajoutez ces lignes pour inclure la bibliothèque uFCoder
LIBS += -LC:/Libraries/uFCoder -luFCoder
INCLUDEPATH += C:/Libraries/uFCoder/include

    QT       += core gui printsupport serialport bluetooth

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Common_wave.cpp \
    SimpleCircularBuffer.cpp \
    circularprogessbar.cpp \
    common.cpp \
    dataprocessor.cpp \
    infowindow.cpp \
    main.cpp \
    mainwindow.cpp \
    myComboBox.cpp \
    qcustomplot.cpp \
    vProgressBars.cpp

HEADERS += \
    Common_wave.h \
    HC05.h \
    Resp_filter.h \
    SimpleCircularBuffer.h \
    circularprogessbar.h \
    common.h \
    dataprocessor.h \
    infowindow.h \
    lib-qt-qml-tricks/src/qqmlhelpers.h \
    mainwindow.h \
    myComboBox.h \
    qcustomplot.h \
    vProgressBars.h

FORMS += \
    Infowindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


# 中文乱码解决
win32-msvc* {
    QMAKE_CXXFLAGS += /source-charset:utf-8 /execution-charset:utf-8
}

RESOURCES += \
    images.qrc




TEMPLATE = app

QT += qml quick core gui quickwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11


DEFINES += QT_DEPRECATED_WARNINGS
DEFINES -= UNICODE

SOURCES += main.cpp \
    hconnectioncontroller.cpp \
    hcontroller.cpp \
    hdbcontroller.cpp \
    hscreenuiwidget.cpp \
    hscreenwidget.cpp \
    hstreamcontroller.cpp

DISTFILES += \
    backend.js

HEADERS += \
    hconnectioncontroller.h \
    hcontroller.h \
    hdbcontroller.h \
    hrdpenums.h \
    hscreenuiwidget.h \
    hscreenwidget.h \
    hstreamcontroller.h

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)
include($$(HARF_DIR)/lib/include/path.pri)
include($$(HARF_DIR)/lib/include/platform.pri)
include($$(HARF_DIR)/lib/include/harfqt.pri)
include($$(HARF_DIR)/lib/include/harfdb.pri)
include($$(HARF_DIR)/lib/include/arengine.pri)
include($$(HARF_DIR)/lib/include/osg.pri)
include($$(HARF_DIR)/lib/include/opencv.pri)
include($$(HARF_DIR)/lib/include/openssl.pri)
include($$(HARF_DIR)/lib/include/shared.pri)
include($$(HARF_DIR)/lib/include/harfconnection.pri)
include($$(HARF_DIR)/lib/include/enet.pri)
include($$(HARF_DIR)/lib/include/pjproject.pri)
include($$(HARF_DIR)/lib/include/stream.pri)
include($$(HARF_DIR)/lib/include/gstreamer.pri)
include($$(HARF_DIR)/lib/include/harfcore.pri)
include($$(HARF_DIR)/lib/include/harfutils.pri)
include($$(HARF_DIR)/lib/include/harfprotobuf.pri)
include($$(HARF_DIR)/lib/include/cpprestsdk.pri)
include($$(HARF_DIR)/lib/include/boost.pri)
include($$(HARF_DIR)/lib/include/breakpad.pri)

APPNAME = $$basename(PWD)

CONFIG(debug, debug|release) {
    DESTDIR = $$(HARF_DIR)/lib/$$APPNAME/$$OS/$$COMPILER/debug
} else {
    TARGET = "$$APPNAME"
    DESTDIR = $$(HARF_DIR)/lib/$$APPNAME/$$OS/$$COMPILER/release
}

FORMS += \
    hscreenwidget.ui

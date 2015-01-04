include(../plugin.pri)
include(3rdparty/qxt/qxt.pri)

QT *= gui
greaterThan(QT_MAJOR_VERSION, 4) {
    QT *= widgets
}

SOURCES += \
	baseintegration.cpp \
    baseintegrationtray.cpp

HEADERS += \
	baseintegration.h \
	baseintegrationtray.h \
	../trayinterface.h

RESOURCES += \
    base.qrc

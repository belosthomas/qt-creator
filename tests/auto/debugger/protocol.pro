QT = core network

QTC_LIB_DEPENDS += utils
include(../qttest.pri)

DEBUGGERDIR = $$IDE_SOURCE_TREE/src/plugins/debugger

INCLUDEPATH += $$DEBUGGERDIR

SOURCES += \
    tst_protocol.cpp \
    $$DEBUGGERDIR/debuggerprotocol.cpp

HEADERS += \
    $$DEBUGGERDIR/debuggerprotocol.h

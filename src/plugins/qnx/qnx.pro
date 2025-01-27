QT += network xml

include(../../qtcreatorplugin.pri)

SOURCES += qnxplugin.cpp \
    qnxutils.cpp \
    qnxdevicewizard.cpp \
    qnxrunconfiguration.cpp \
    qnxanalyzesupport.cpp \
    qnxdebugsupport.cpp \
    qnxqtversion.cpp \
    qnxdevice.cpp \
    qnxdevicetester.cpp \
    qnxdeviceprocesssignaloperation.cpp \
    qnxdeviceprocesslist.cpp \
    qnxtoolchain.cpp \
    slog2inforunner.cpp \
    qnxconfiguration.cpp \
    qnxconfigurationmanager.cpp \
    qnxsettingspage.cpp \
    qnxversionnumber.cpp \
    qnxdeployqtlibrariesdialog.cpp \
    qnxdeviceprocess.cpp

HEADERS += qnxplugin.h\
    qnxconstants.h \
    qnxutils.h \
    qnxdevicewizard.h \
    qnxrunconfiguration.h \
    qnxanalyzesupport.h \
    qnxdebugsupport.h \
    qnxqtversion.h \
    qnxdevice.h \
    qnxdevicetester.h \
    qnxdeviceprocesssignaloperation.h \
    qnxdeviceprocesslist.h \
    qnxtoolchain.h \
    slog2inforunner.h \
    qnxconfiguration.h \
    qnxconfigurationmanager.h \
    qnxsettingspage.h \
    qnxversionnumber.h \
    qnxdeployqtlibrariesdialog.h \
    qnx_export.h \
    qnxdeviceprocess.h

FORMS += \
    qnxsettingswidget.ui \
    qnxdeployqtlibrariesdialog.ui


DEFINES += QNX_LIBRARY

RESOURCES += \
    qnx.qrc

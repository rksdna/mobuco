
TEMPLATE = app

QT += core gui widgets

include(../translations/translations.pri)
include(../common/common.pri)

TARGET = $$DEPLOY_TARGET
target.path = $$DEPLOY_BIN_DIR

INCLUDEPATH += \
    commands \
    dialogs \
    delegates

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    ScheduleWidget.cpp \
    dialogs/OpenScheduleDialog.cpp \
    dialogs/SaveScheduleDialog.cpp \
    dialogs/PickScheduleDialog.cpp \
    dialogs/PickScheduleModel.cpp \
    ScheduleModel.cpp \
    ScheduleEntry.cpp \
    ScheduleDelegate.cpp \
    delegates/Delegate.cpp \
    delegates/EnumerationDelegate.cpp

HEADERS += \
    MainWindow.h \
    ScheduleWidget.h \
    dialogs/OpenScheduleDialog.h \
    dialogs/SaveScheduleDialog.h \
    dialogs/PickScheduleDialog.h \
    dialogs/PickScheduleModel.h \
    ScheduleModel.h \
    ScheduleEntry.h \
    ScheduleDelegate.h \
    delegates/Delegate.h \
    delegates/EnumerationDelegate.h

RESOURCES += \
    application.qrc

INSTALLS += \
    target

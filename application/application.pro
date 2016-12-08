
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
    commands/Command.cpp \
    commands/NewCommand.cpp \
    commands/OpenCommand.cpp \
    commands/SaveCommand.cpp \
    commands/CloseCommand.cpp \
    ScheduleModel.cpp \
    ScheduleEntry.cpp \
    ScheduleDelegate.cpp \
    delegates/Delegate.cpp

HEADERS += \
    MainWindow.h \
    ScheduleWidget.h \
    dialogs/OpenScheduleDialog.h \
    dialogs/SaveScheduleDialog.h \
    dialogs/PickScheduleDialog.h \
    dialogs/PickScheduleModel.h \
    commands/Command.h \
    commands/NewCommand.h \
    commands/OpenCommand.h \
    commands/SaveCommand.h \
    commands/CloseCommand.h \
    ScheduleModel.h \
    ScheduleEntry.h \
    ScheduleDelegate.h \
    delegates/Delegate.h

RESOURCES += \
    application.qrc

INSTALLS += \
    target

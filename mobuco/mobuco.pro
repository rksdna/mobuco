
TEMPLATE = app

QT += core gui widgets

include(../translations/translations.pri)
include(../common/common.pri)

TARGET = $$DEPLOY_TARGET
target.path = $$DEPLOY_BIN_DIR

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    ScheduleWidget.cpp \
    OpenScheduleDialog.cpp \
    SaveScheduleDialog.cpp \
    PickScheduleDialog.cpp \
    PickScheduleModel.cpp

HEADERS += \
    MainWindow.h \
    ScheduleWidget.h \
    OpenScheduleDialog.h \
    SaveScheduleDialog.h \
    PickScheduleDialog.h \
    PickScheduleModel.h

RESOURCES += \
    mobuco.qrc

INSTALLS += \
    target

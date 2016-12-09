
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
    delegates/Delegate.cpp \
    delegates/EnumerationDelegate.cpp \
    SchemeDelegate.cpp \
    SchemeModel.cpp \
    SchemeEntry.cpp \
    SchemeWidget.cpp \
    dialogs/OpenSchemeDialog.cpp \
    dialogs/PickSchemeDialog.cpp \
    dialogs/PickSchemeModel.cpp \
    dialogs/SaveSchemeDialog.cpp

HEADERS += \
    MainWindow.h \
    delegates/Delegate.h \
    delegates/EnumerationDelegate.h \
    SchemeEntry.h \
    SchemeDelegate.h \
    SchemeWidget.h \
    SchemeModel.h \
    dialogs/OpenSchemeDialog.h \
    dialogs/PickSchemeDialog.h \
    dialogs/PickSchemeModel.h \
    dialogs/SaveSchemeDialog.h

RESOURCES += \
    application.qrc

INSTALLS += \
    target

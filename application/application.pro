
TEMPLATE = app

QT += core gui widgets

include(../translations/translations.pri)
include(../common/common.pri)

TARGET = $$DEPLOY_TARGET
target.path = $$DEPLOY_BIN_DIR

INCLUDEPATH += \
    schemes \
    dialogs \
    delegates \
    functions

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    delegates/Delegate.cpp \
    schemes/SchemeDelegate.cpp \
    schemes/SchemeModel.cpp \
    schemes/SchemeWidget.cpp \
    dialogs/OpenSchemeDialog.cpp \
    dialogs/SaveSchemeDialog.cpp \
    dialogs/SelectSchemeModel.cpp \
    dialogs/SelectSchemeDialog.cpp \
    schemes/SchemeItem.cpp \
    functions/Function.cpp \
    functions/ReadRegistersFunction.cpp \
    functions/FunctionType.cpp \
    delegates/FunctionDelegate.cpp \
    delegates/DefaultDelegate.cpp

HEADERS += \
    MainWindow.h \
    delegates/Delegate.h \
    schemes/SchemeDelegate.h \
    schemes/SchemeWidget.h \
    schemes/SchemeModel.h \
    dialogs/OpenSchemeDialog.h \
    dialogs/SaveSchemeDialog.h \
    dialogs/SelectSchemeDialog.h \
    dialogs/SelectSchemeModel.h \
    schemes/SchemeItem.h \
    functions/Function.h \
    functions/ReadRegistersFunction.h \
    functions/FunctionType.h \
    delegates/FunctionDelegate.h \
    delegates/DefaultDelegate.h

RESOURCES += \
    application.qrc

INSTALLS += \
    target

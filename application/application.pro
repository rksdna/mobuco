
TEMPLATE = app

QT += core gui widgets

include(../translations/translations.pri)
include(../common/common.pri)

TARGET = $$DEPLOY_TARGET
target.path = $$DEPLOY_BIN_DIR

INCLUDEPATH += \
    schemes \
    dialogs \
    delegates

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    delegates/Delegate.cpp \
    delegates/EnumerationDelegate.cpp \
    schemes/SchemeDelegate.cpp \
    schemes/SchemeModel.cpp \
    schemes/SchemeWidget.cpp \
    dialogs/OpenSchemeDialog.cpp \
    dialogs/SaveSchemeDialog.cpp \
    dialogs/SelectSchemeModel.cpp \
    dialogs/SelectSchemeDialog.cpp \
    schemes/SchemeItem.cpp

HEADERS += \
    MainWindow.h \
    delegates/Delegate.h \
    delegates/EnumerationDelegate.h \
    schemes/SchemeDelegate.h \
    schemes/SchemeWidget.h \
    schemes/SchemeModel.h \
    dialogs/OpenSchemeDialog.h \
    dialogs/SaveSchemeDialog.h \
    dialogs/SelectSchemeDialog.h \
    dialogs/SelectSchemeModel.h \
    schemes/SchemeItem.h

RESOURCES += \
    application.qrc

INSTALLS += \
    target

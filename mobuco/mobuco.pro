
TEMPLATE = app

QT += core gui widgets

include(../translations/translations.pri)

TARGET = $$DEPLOY_TARGET
target.path = $$DEPLOY_BIN_DIR

SOURCES += \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    MainWindow.h

RESOURCES += \
    mobuco.qrc

INSTALLS += \
    target

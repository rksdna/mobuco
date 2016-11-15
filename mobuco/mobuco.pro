
TEMPLATE = app

QT += core gui widgets

include(../translations/translations.pri)

TARGET = $$MOBUCO_BIN_FILE
target.path = $$MOBUCO_BIN_DIR

SOURCES += \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    MainWindow.h

RESOURCES += \
    mobuco.qrc

INSTALLS += \
    target

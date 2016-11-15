MOBUCO_NAME = MoBuCo
MOBUCO_BIN_FILE = mobuco
MOBUCO_BIN_DIR = /usr/bin
MOBUCO_DATA_DIR = /usr/share/mobuco

isEmpty(MOBUCO_VERSION): MOBUCO_VERSION = $$system(git rev-list --count master)

VERSION = $$MOBUCO_VERSION

DEFINES += \
    MOBUCO_NAME=\\\"$$MOBUCO_NAME\\\" \
    MOBUCO_BIN_FILE=\\\"$$MOBUCO_BIN_FILE\\\" \
    MOBUCO_BIN_DIR=\\\"$$MOBUCO_BIN_DIR\\\" \
    MOBUCO_DATA_DIR=\\\"$$MOBUCO_DATA_DIR\\\" \
    MOBUCO_VERSION=\\\"$$MOBUCO_VERSION\\\"

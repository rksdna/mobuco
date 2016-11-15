
DEPLOY_NAME = MoBuCo
DEPLOY_DOMAIN = www.mobuco.com
DEPLOY_ORGANIZATION = none
DEPLOY_TARGET = mobuco
DEPLOY_BIN_DIR = /usr/bin
DEPLOY_DATA_DIR = /usr/share/mobuco

isEmpty(DEPLOY_VERSION): DEPLOY_VERSION = 0.$$system(git rev-list --count master)
isEmpty(DEPLOY_DATE): DEPLOY_DATE = $$system(date -R)

VERSION = $$DEPLOY_VERSION

DEFINES += \
    DEPLOY_NAME='"\\\"$$DEPLOY_NAME\\\""' \
    DEPLOY_DOMAIN='"\\\"$$DEPLOY_DOMAIN\\\""' \
    DEPLOY_ORGANIZATION='"\\\"$$DEPLOY_ORGANIZATION\\\""' \
    DEPLOY_BIN_DIR='"\\\"$$DEPLOY_BIN_DIR\\\""' \
    DEPLOY_DATA_DIR='"\\\"$$DEPLOY_DATA_DIR\\\""' \
    DEPLOY_VERSION='"\\\"$$DEPLOY_VERSION\\\""' \
    DEPLOY_DATE='"\\\"$$DEPLOY_DATE\\\""'

OTHER_FILES += \
    $$PWD/changelog \
    $$PWD/control \
    $$PWD/copyright \
    $$PWD/manpage \
    $$PWD/deploy.sh

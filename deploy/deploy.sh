#!/bin/sh

set -e

if [ ! -d "$1" ] || [ ! -d "$2" ] ; then
    echo "\n\tUsage: $0 <Source directory> <Target directory>\n\t\tSource directory must contains project file\n"
    exit 1;
fi

SOURCE_DIR=$(readlink -f $1)
TARGET_DIR=$(readlink -f $2)
BUILD_DIR=$(mktemp -d -p /tmp)

DEPLOY_VERSION=1.$(git rev-list --count master)
DEPLOY_DATE=$(date -R)

PACKAGE_NAME=$(sed -n 's/^Package: //p' $SOURCE_DIR/deploy/control)
PACKAGE_VERSION=$DEPLOY_VERSION
PACKAGE_ARCHITECTURE=$(sed -n 's/^Architecture: //p' $SOURCE_DIR/deploy/control)

PACKAGE=$PACKAGE_NAME'_'$PACKAGE_VERSION'_'$PACKAGE_ARCHITECTURE
PACKAGE_DIR=$BUILD_DIR/$PACKAGE
PACKAGE_FILE=$BUILD_DIR/$PACKAGE.deb
PACKAGE_DATA_DIR=$PACKAGE_DIR/usr/share/$PACKAGE_NAME
PACKAGE_DOC_DIR=$PACKAGE_DIR/usr/share/doc/$PACKAGE_NAME
PACKAGE_MAN_DIR=$PACKAGE_DIR/usr/share/man/man1/
DEBIAN_DIR=$PACKAGE_DIR/DEBIAN

echo "Package: $PACKAGE"
echo "Source: $SOURCE_DIR"
echo "Target: $TARGET_DIR"
echo "Version: $DEPLOY_VERSION"
echo "Date: $DEPLOY_DATE"
echo

mkdir -p $PACKAGE_DIR
mkdir -p $DEBIAN_DIR
mkdir -p $PACKAGE_DATA_DIR
mkdir -p $PACKAGE_DOC_DIR
mkdir -p $PACKAGE_MAN_DIR

install -m 644 -p $SOURCE_DIR/deploy/control $DEBIAN_DIR
install -m 644 -p $SOURCE_DIR/deploy/copyright $PACKAGE_DOC_DIR
install -m 644 -p $SOURCE_DIR/deploy/changelog $PACKAGE_DOC_DIR
install -m 644 -p $SOURCE_DIR/deploy/manpage $PACKAGE_MAN_DIR/$PACKAGE_NAME.1

echo "-- control --"
sed  -i -e "s/__VERSION__/$DEPLOY_VERSION/g" $DEBIAN_DIR/control
cat $DEBIAN_DIR/control
echo

echo "-- changelog --"
sed  -i -e "s/__VERSION__/$DEPLOY_VERSION/g" $PACKAGE_DOC_DIR/changelog
sed  -i -e "s/__DATE__/$DEPLOY_DATE/g" $PACKAGE_DOC_DIR/changelog
cat $PACKAGE_DOC_DIR/changelog
echo

echo "-- copyright --"
cat $PACKAGE_DOC_DIR/copyright
echo

gzip -9 $PACKAGE_DOC_DIR/changelog
gzip -9 $PACKAGE_MAN_DIR/$PACKAGE_NAME.1

cd $BUILD_DIR

/usr/lib/x86_64-linux-gnu/qt5/bin/qmake "DEPLOY_DATE=$DEPLOY_DATE" "DEPLOY_VERSION=$DEPLOY_VERSION" $SOURCE_DIR
make -j5 install INSTALL_ROOT=$PACKAGE_DIR

fakeroot dpkg-deb --build $PACKAGE_DIR
lintian $PACKAGE_FILE

cp -f $PACKAGE_FILE $TARGET_DIR

exit 0

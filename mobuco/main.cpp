#include <QDebug>
#include <QTranslator>
#include <QLibraryInfo>
#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    application.setApplicationName(MOBUCO_NAME);
    application.setApplicationVersion(MOBUCO_VERSION);

    qDebug() << MOBUCO_NAME;
    qDebug() << MOBUCO_VERSION;
    qDebug() << MOBUCO_BIN_FILE;
    qDebug() << MOBUCO_BIN_DIR;
    qDebug() << MOBUCO_DATA_DIR;

    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    application.installTranslator(&qtTranslator);

    QTranslator transaltor;
#ifdef QT_DEBUG
    transaltor.load("tr_" + QLocale::system().name());
#else
    transaltor.load("tr_" + QLocale::system().name(), MOBUCO_DATA_DIR);
#endif
    application.installTranslator(&transaltor);

    MainWindow window;
    window.show();

    return application.exec();
}

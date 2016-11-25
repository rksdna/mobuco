#include <QDebug>
#include <QDateTime>
#include <QTranslator>
#include <QLibraryInfo>
#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    application.setApplicationName(DEPLOY_NAME);
    application.setApplicationDisplayName(DEPLOY_NAME);
    application.setApplicationVersion(DEPLOY_VERSION);
    application.setOrganizationDomain(DEPLOY_DOMAIN);
    application.setOrganizationName(DEPLOY_ORGANIZATION);

    qDebug() << DEPLOY_NAME;
    qDebug() << DEPLOY_DOMAIN;
    qDebug() << DEPLOY_ORGANIZATION;
    qDebug() << DEPLOY_BIN_DIR;
    qDebug() << DEPLOY_DATA_DIR;
    qDebug() << DEPLOY_VERSION;
    qDebug() << DEPLOY_DATE;

    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    application.installTranslator(&qtTranslator);

    QTranslator appTranslator;
#ifdef QT_DEBUG
    appTranslator.load("tr_" + QLocale::system().name());
#else
    appTranslator.load("tr_" + QLocale::system().name(), DEPLOY_DATA_DIR);
#endif
    application.installTranslator(&appTranslator);

    MainWindow window;
    window.show();

    return application.exec();
}

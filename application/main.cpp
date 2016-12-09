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

#include <QMenu>
#include <QMenuBar>
#include <QSettings>
#include <QApplication>
#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(QApplication::instance()->applicationName());

    QMenu * const fileMenu = menuBar()->addMenu(tr("&File"));
    QAction * const closeAction = fileMenu->addAction(tr("E&xit"));
    connect(closeAction, &QAction::triggered, this, &MainWindow::close);

    QSettings settings;
    restoreGeometry(settings.value("MainWindow/Geometry").toByteArray());
    restoreState(settings.value("MainWindow/State").toByteArray());
}

MainWindow::~MainWindow()
{
    QSettings settings;
    settings.setValue("MainWindow/Geometry", saveGeometry());
    settings.setValue("MainWindow/State", saveState());
}


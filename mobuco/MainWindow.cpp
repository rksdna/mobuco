#include <QMenu>
#include <QDebug>
#include <QMenuBar>
#include <QSettings>
#include <QTabWidget>
#include <QApplication>
#include "MainWindow.h"
#include "ScheduleWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_tabWidget(new QTabWidget)
{
    setCentralWidget(m_tabWidget);

    m_tabWidget->setTabsClosable(true);
    connect(m_tabWidget, &QTabWidget::currentChanged, this, &MainWindow::updateWindowHeader);
    connect(m_tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::closeFileByIndex);

    QMenu * const fileMenu = menuBar()->addMenu(tr("File"));

    QAction * const createFileAction = fileMenu->addAction(tr("New"));
    createFileAction->setShortcut(QKeySequence::New);
    connect(createFileAction, &QAction::triggered, this, &MainWindow::createFile);

    QAction * const openFileAction = fileMenu->addAction(tr("Open"));
    openFileAction->setShortcut(QKeySequence::Open);
    connect(openFileAction, &QAction::triggered, this, &MainWindow::openFile);

    fileMenu->addSeparator();

    QAction * const saveAction = fileMenu->addAction(tr("Save"));
    saveAction->setShortcut(QKeySequence::Save);
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveFile);

    QAction * const saveAsAction = fileMenu->addAction(tr("Save as.."));
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::saveFileAs);

    QAction * const saveAllAction = fileMenu->addAction(tr("Save all"));
    connect(saveAllAction, &QAction::triggered, this, &MainWindow::saveAllFiles);

    fileMenu->addSeparator();

    QAction * const closeAction = fileMenu->addAction(tr("Close"));
    closeAction->setShortcut(QKeySequence::Close);
    connect(closeAction, &QAction::triggered, this, &MainWindow::closeFile);

    QAction * const closeAllAction = fileMenu->addAction(tr("Close All"));
    connect(closeAllAction, &QAction::triggered, this, &MainWindow::closeAllFiles);

    fileMenu->addSeparator();

    QAction * const exitAction = fileMenu->addAction(tr("Exit"));
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, this, &MainWindow::close);

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

void MainWindow::createFile()
{
    ScheduleWidget * const widget = new ScheduleWidget;
    connect(widget, &ScheduleWidget::modified, this, &MainWindow::updateTabHeader);
    m_tabWidget->addTab(widget, QString());

    widget->createNew();
}

void MainWindow::openFile()
{
}

void MainWindow::saveFile()
{
}

void MainWindow::saveFileAs()
{
}

void MainWindow::saveAllFiles()
{
}

void MainWindow::closeFile()
{
}

void MainWindow::closeFileByIndex(int index)
{
    m_tabWidget->widget(index)->deleteLater();
}

void MainWindow::closeAllFiles()
{
}

void MainWindow::updateTabHeader(ScheduleWidget *widget)
{
    const QString title = (widget->isModified() ? tr("%1*") : tr("%1")).arg(widget->fileName());
    m_tabWidget->setTabText(m_tabWidget->indexOf(widget), title);

    if (widget == currentWidget())
        updateWindowHeader();
}

void MainWindow::updateWindowHeader()
{
    ScheduleWidget * const widget = currentWidget();
    setWindowFilePath(widget ? widget->fileName() : QString());
    setWindowModified(widget ? widget->isModified() : false);
}

ScheduleWidget *MainWindow::currentWidget() const
{
    return qobject_cast<ScheduleWidget *>(m_tabWidget->currentWidget());
}

#include <QMenu>
#include <QDebug>
#include <QMenuBar>
#include <QSettings>
#include <QTabWidget>
#include <QCloseEvent>
#include <QApplication>
#include "MainWindow.h"
#include "ScheduleWidget.h"
#include "MainWindowCommand.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_widget(new QTabWidget)
{
    setCentralWidget(m_widget);

    m_widget->setTabsClosable(true);
    connect(m_widget, &QTabWidget::currentChanged, this, &MainWindow::updateWindowHeader);
    connect(m_widget, &QTabWidget::tabCloseRequested, this, &MainWindow::closeFileByIndex);

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

void MainWindow::appendItem(ScheduleWidget *item)
{
    m_widget->addTab(item, QString());
    connect(item, &ScheduleWidget::statusChanged, this, &MainWindow::updateTabHeader);
    updateTabHeader(item);
}

void MainWindow::removeItem(ScheduleWidget *item)
{
    m_widget->removeTab(m_widget->indexOf(item));
    item->deleteLater();
}

void MainWindow::hideEvent(QHideEvent *event)
{
    QSettings settings;
    settings.setValue("MainWindow/Geometry", saveGeometry());
    settings.setValue("MainWindow/State", saveState());

    QMainWindow::hideEvent(event);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (!items().isEmpty())
    {
        CloseCommand * const command = new CloseCommand(items(), this);
        connect(command, &CloseCommand::completed, this, &MainWindow::close, Qt::QueuedConnection);

        command->execute();
        event->ignore();
        return;
    }

    QMainWindow::closeEvent(event);
}

void MainWindow::createFile()
{
    NewCommand * const command = new NewCommand(this);
    command->execute();
}

void MainWindow::openFile()
{
    OpenCommand * const command = new OpenCommand(this);
    command->execute();
}

void MainWindow::saveFile()
{
    SaveCommand * const command = new SaveCommand(items(m_widget->currentIndex()), this);
    command->execute();
}

void MainWindow::saveFileAs()
{
    SaveCommand * const command = new SaveCommand(items(m_widget->currentIndex()), this);
    command->setAskFileName(true);
    command->execute();
}

void MainWindow::saveAllFiles()
{
    SaveCommand * const command = new SaveCommand(items(), this);
    command->execute();
}

void MainWindow::closeFile()
{
    CloseCommand * const command = new CloseCommand(items(m_widget->currentIndex()), this);
    command->execute();
}

void MainWindow::closeFileByIndex(int index)
{
    CloseCommand * const command = new CloseCommand(items(index), this);
    command->execute();
}

void MainWindow::closeAllFiles()
{
    CloseCommand * const command = new CloseCommand(items(), this);
    command->execute();
}

void MainWindow::updateTabHeader(ScheduleWidget *item)
{
    const QString title = (item->isModified() ? tr("%1*") : tr("%1")).arg(item->fileName());
    m_widget->setTabText(m_widget->indexOf(item), title);

    updateWindowHeader();
}

void MainWindow::updateWindowHeader()
{
    ScheduleWidget * const item = itemByIndex(m_widget->currentIndex());
    setWindowFilePath(item ? item->fileName() : QString());
    setWindowModified(item ? item->isModified() : false);
}

QList<ScheduleWidget *> MainWindow::items() const
{
    QList<ScheduleWidget *> items;
    for (int index = 0; index < m_widget->count(); index++)
        items.append(itemByIndex(index));

    return items;
}

QList<ScheduleWidget *> MainWindow::items(int index) const
{
    QList<ScheduleWidget *> items;
    if (itemByIndex(index))
        items.append(itemByIndex(index));

    return items;
}

ScheduleWidget *MainWindow::itemByIndex(int index) const
{
    return qobject_cast<ScheduleWidget *>(m_widget->widget(index));
}

#include <QMenu>
#include <QDebug>
#include <QMenuBar>
#include <QSettings>
#include <QTabWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QCloseEvent>
#include <QApplication>
#include "FileDialog.h"
#include "ListDialog.h"
#include "MainWindow.h"
#include "ScheduleWidget.h"

MainWindow::Command::Command(MainWindow::Command::Type type)
    : type(type),
      widget(0)
{
}

MainWindow::Command::Command(MainWindow::Command::Type type, ScheduleWidget *widget)
    : type(type),
      widget(widget),
      argument(widget->isNew() ? QString() : widget->fileName())
{
}

MainWindow::Command::Command(MainWindow::Command::Type type, ScheduleWidget *widget, const QString &argument)
    : type(type),
      widget(widget),
      argument(argument)
{
}

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

void MainWindow::hideEvent(QHideEvent *event)
{
    QSettings settings;
    settings.setValue("MainWindow/Geometry", saveGeometry());
    settings.setValue("MainWindow/State", saveState());

    QMainWindow::hideEvent(event);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (m_tabWidget->count())
    {
        event->ignore();

        m_batch.clear();
        foreach (ScheduleWidget *widget, all())
            m_batch.append(Command(Command::Close, widget));

        m_batch.append(Command(Command::Quit, 0, QString()));
        executeBatch();
        return;
    }

    QMainWindow::closeEvent(event);
}

void MainWindow::createFile()
{
    m_batch.clear();
    m_batch.append(Command(Command::New, createWidget(), tr("new.json")));

    executeBatch();
}

void MainWindow::openFile()
{
    FileDialog * const dialog  = new FileDialog(FileDialog::OpenFiles, this);
    connect(dialog, &QFileDialog::filesSelected, this, &MainWindow::openSelectedFiles);

    dialog->open();
}

void MainWindow::openSelectedFiles(const QStringList &fileNames)
{
    m_batch.clear();
    foreach (const QString &fileName, fileNames)
        m_batch.append(Command(Command::Open, createWidget(), fileName));

    executeBatch();
}

void MainWindow::saveFile()
{
    m_batch.clear();
    m_batch.append(Command(Command::Save, currentWidget()));

    executeBatch();
}

void MainWindow::saveFileAs()
{
    m_batch.clear();
    m_batch.append(Command(Command::Save, currentWidget(), QString()));

    executeBatch();
}

void MainWindow::saveAllFiles()
{
    m_batch.clear();
    foreach (ScheduleWidget *widget, all())
        m_batch.append(Command(Command::Save, widget));

    executeBatch();
}

void MainWindow::closeFile()
{
    m_batch.clear();
    m_batch.append(Command(Command::Close, currentWidget()));

    executeBatch();
}

void MainWindow::closeFileByIndex(int index)
{
    m_batch.clear();
    m_batch.append(Command(Command::Close, widget(index)));

    executeBatch();
}

void MainWindow::closeAllFiles()
{
    m_batch.clear();
    foreach (ScheduleWidget *widget, all())
        m_batch.append(Command(Command::Close, widget));

    executeBatch();
}

void MainWindow::setBatchArgument(const QString &argument)
{
    m_batch.first().argument = argument;
    executeBatch();
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

void MainWindow::showErrorMessage(const QString &text)
{
    QMessageBox * const box = new QMessageBox(this);
    box->setIcon(QMessageBox::Critical);
    box->setText(text);
    connect(box, &QMessageBox::finished, box, &QMessageBox::deleteLater);

    box->open();
}

ScheduleWidget *MainWindow::createWidget()
{
    ScheduleWidget * const widget = new ScheduleWidget;
    m_tabWidget->addTab(widget, QString());
    connect(widget, &ScheduleWidget::modified, this, &MainWindow::updateTabHeader);

    return widget;
}

ScheduleWidget *MainWindow::currentWidget() const
{
    return qobject_cast<ScheduleWidget *>(m_tabWidget->currentWidget());
}

ScheduleWidget *MainWindow::widget(int index) const
{
    return qobject_cast<ScheduleWidget *>(m_tabWidget->widget(index));
}

QList<ScheduleWidget *> MainWindow::all() const
{
    QList<ScheduleWidget *> result;
    for (int i = 0; i < m_tabWidget->count(); i++)
        result.append(widget(i));

    return result;
}

QList<ScheduleWidget *> MainWindow::modified() const
{
    QList<ScheduleWidget *> result;
    for (int i = 0; i < m_tabWidget->count(); i++)
    {
        if (widget(i)->isModified())
            result.append(widget(i));
    }

    return result;
}

void MainWindow::executeBatch()
{
    QList<ScheduleWidget *> wc;

    foreach (const Command &cmd, m_batch)
    {
        if ((cmd.type == Command::Close) && cmd.widget->isModified())
        {
            wc.append(cmd.widget);
        }
    }

    if (wc.isEmpty())
        adjustedBatch();
    else
    {
        ListDialog * const dialog = new ListDialog(wc, this);
        connect(dialog, &ListDialog::selected, this, &MainWindow::adjBatch);

        dialog->open();
    }
}

void MainWindow::adjBatch(QList<ScheduleWidget *> w)
{
    foreach (ScheduleWidget *widget, w)
        m_batch.prepend(Command(Command::Save, widget));

    adjustedBatch();
}

void MainWindow::adjustedBatch()
{
    const Command command = m_batch.first();
    switch (command.type)
    {
    case Command::New:
        command.widget->createNew(command.argument);
        break;

    case Command::Open:
        if (!command.widget->loadFromFile(command.argument))
        {
            showErrorMessage(tr("Can't open: %1").arg(command.argument));
            return;
        }
        break;

    case Command::Save:
        if (command.argument.isEmpty())
        {
            FileDialog * const dialog  = new FileDialog(FileDialog::SaveFile, this);
            dialog->selectFile(m_batch.first().widget->fileName());
            connect(dialog, &QFileDialog::fileSelected, this, &MainWindow::setBatchArgument);

            dialog->open();
            return;
        }

        if (!command.widget->saveToFile(command.argument))
        {
            showErrorMessage(tr("Can't save: %1").arg(command.argument));
            return;
        }
        break;

    case Command::Close:
        m_tabWidget->removeTab(m_tabWidget->indexOf(command.widget));
        command.widget->deleteLater();
        break;

    case Command::Quit:
        close();
        break;

    default:
        break;
    }

    m_batch.removeFirst();
    if (!m_batch.isEmpty())
        adjustedBatch();
}



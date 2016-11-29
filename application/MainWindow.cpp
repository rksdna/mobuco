#include <QMenu>
#include <QTimer>
#include <QDebug>
#include <QMenuBar>
#include <QSettings>
#include <QTabWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QCloseEvent>
#include <QApplication>
#include "MainWindow.h"
#include "ScheduleWidget.h"
#include "SaveScheduleDialog.h"
#include "OpenScheduleDialog.h"
#include "PickScheduleDialog.h"

Controller::Controller(QWidget *parent)
    : QObject(parent),
      m_widget(parent)
{
}

QWidget *Controller::widget() const
{
    return m_widget;
}


SaveController::SaveController(const QList<ScheduleWidget *> &items, QWidget *parent)
    : Controller(parent),
      m_items(items)
{
}

SaveController::~SaveController()
{
    qDebug() << "Save bue";
}

void SaveController::process()
{
    while (!m_items.isEmpty())
    {
        ScheduleWidget * const item = m_items.first();

        if (item->isNew() && m_fileName.isEmpty())
        {
            SaveScheduleDialog * const dialog = new SaveScheduleDialog(item->fileName(), widget());
            connect(dialog, &OpenScheduleDialog::finished, dialog, &OpenScheduleDialog::deleteLater);
            connect(dialog, &OpenScheduleDialog::rejected, this, &SaveController::stopped);

            connect(dialog, &OpenScheduleDialog::fileSelected, this, &SaveController::save);

            dialog->open();
            return;
        }
        else
        {
            if (!item->isNew())
                m_fileName = item->fileName();

            if (!item->saveToFile(m_fileName))
            {
                qDebug() << "SHIT";
                emit stopped();
                return;
            }

            emit saved(item);
            m_items.removeFirst();
            m_fileName.clear();
        }
    }

    qDebug() << "Save done";
    emit processed();
}

void SaveController::save(const QString &fileName)
{
    m_fileName = fileName;
    process();
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
    QMainWindow::closeEvent(event);
}

void MainWindow::createFile()
{
    static int n = 1;
    createItem()->createNew(tr("%1.json").arg(n++));
}

void MainWindow::openFile()
{

}

void MainWindow::openSelectedFiles(const QStringList &fileNames)
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
    SaveController * const c = new SaveController(items(), this);
    connect(c, &SaveController::processed, c, &SaveController::deleteLater);
    connect(c, &SaveController::stopped, c, &SaveController::deleteLater);

    c->process();
}

void MainWindow::closeFile()
{

}

void MainWindow::closeFileByIndex(int index)
{

}

void MainWindow::closeAllFiles()
{

}

void MainWindow::updateTabHeader(ScheduleWidget *widget)
{
    const QString title = (widget->isModified() ? tr("%1*") : tr("%1")).arg(widget->fileName());
    m_tabWidget->setTabText(m_tabWidget->indexOf(widget), title);

    if (widget == currentItem())
        updateWindowHeader();
}

void MainWindow::updateWindowHeader()
{
    ScheduleWidget * const widget = currentItem();
    setWindowFilePath(widget ? widget->fileName() : QString());
    setWindowModified(widget ? widget->isModified() : false);
}

void MainWindow::showOpenDialog()
{
    /*OpenScheduleDialog * const dialog  = new OpenScheduleDialog(this);
    connect(dialog, &OpenScheduleDialog::finished, dialog, &OpenScheduleDialog::deleteLater);
    connect(dialog, &OpenScheduleDialog::filesSelected, this, &MainWindow::openSelectedFiles);

    dialog->open();*/
}

void MainWindow::showSaveDialog(const QString &fileName)
{
    /*SaveScheduleDialog * const dialog  = new SaveScheduleDialog(fileName, this);
    connect(dialog, &OpenScheduleDialog::finished, dialog, &OpenScheduleDialog::deleteLater);
    connect(dialog, &OpenScheduleDialog::fileSelected, this, &MainWindow::saveSelectedFile);

    dialog->open();*/
}

void MainWindow::showPickDialog(const QList<ScheduleWidget *> items)
{
    /*PickScheduleDialog * const dialog = new PickScheduleDialog(tr("Save this files?"), items, this);
    connect(dialog, &PickScheduleDialog::finished, dialog, &PickScheduleDialog::deleteLater);
    connect(dialog, &PickScheduleDialog::selected, this, &MainWindow::_doSave);

    dialog->open();*/
}

void MainWindow::showErrorMessage(const QString &text)
{
    QMessageBox * const box = new QMessageBox(this);
    box->setIcon(QMessageBox::Critical);
    box->setText(text);
    connect(box, &QMessageBox::finished, box, &QMessageBox::deleteLater);

    box->open();
}

ScheduleWidget *MainWindow::createItem()
{
    ScheduleWidget * const widget = new ScheduleWidget;
    m_tabWidget->addTab(widget, QString());
    connect(widget, &ScheduleWidget::modified, this, &MainWindow::updateTabHeader);

    return widget;
}

ScheduleWidget *MainWindow::currentItem() const
{
    return qobject_cast<ScheduleWidget *>(m_tabWidget->currentWidget());
}

ScheduleWidget *MainWindow::item(int index) const
{
    return qobject_cast<ScheduleWidget *>(m_tabWidget->widget(index));
}

QList<ScheduleWidget *> MainWindow::items() const
{
    QList<ScheduleWidget *> result;
    for (int i = 0; i < m_tabWidget->count(); i++)
        result.append(item(i));

    return result;
}



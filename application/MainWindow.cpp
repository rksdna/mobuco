#include <QMenu>
#include <QDebug>
#include <QMenuBar>
#include <QSettings>
#include <QTabWidget>
#include <QMessageBox>
#include <QCloseEvent>
#include <QApplication>
#include "MainWindow.h"
#include "SchemeWidget.h"
#include "SaveSchemeDialog.h"
#include "OpenSchemeDialog.h"
#include "SelectSchemeDialog.h"

template<typename T>
static QList<T> toList(T value)
{
    QList<T> result;
    result.append(value);

    return result;
}

MainWindow::SaveCloseContext::SaveCloseContext()
    : exitAfterClose(false)
{
}

void MainWindow::SaveCloseContext::setSchemesForSave(const QList<SchemeWidget *> &schemes, bool askFileName)
{
    foreach (SchemeWidget *scheme, schemes)
        schemesForSave.insert(scheme, askFileName || scheme->isNew() ? QString() : scheme->fileName());
}

QList<SchemeWidget *> MainWindow::SaveCloseContext::modifiedSchemes() const
{
    QList<SchemeWidget *> schemes;
    foreach (SchemeWidget *scheme, schemesForClose)
    {
        if (scheme->isModified())
            schemes.append(scheme);
    }

    return schemes;
}

SchemeWidget *MainWindow::SaveCloseContext::schemeForSave() const
{
    return schemesForSave.keys(QString()).value(0);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_widget(new QTabWidget)
{
    connect(this, &MainWindow::closeRequested, this, &MainWindow::close, Qt::QueuedConnection);

    setCentralWidget(m_widget);

    // debug
    QIcon::setThemeName("Mint-X");

    m_widget->setTabsClosable(true);
    connect(m_widget, &QTabWidget::currentChanged, this, &MainWindow::updateWindowHeader);
    connect(m_widget, &QTabWidget::tabCloseRequested, this, &MainWindow::closeFileByIndex);

    QMenu * const fileMenu = menuBar()->addMenu(tr("File"));

    QAction * const createFileAction = fileMenu->addAction(QIcon::fromTheme("document-new"), tr("New"));
    createFileAction->setShortcut(QKeySequence::New);
    connect(createFileAction, &QAction::triggered, this, &MainWindow::newFile);

    QAction * const openFileAction = fileMenu->addAction(QIcon::fromTheme("document-open"), tr("Open..."));
    openFileAction->setShortcut(QKeySequence::Open);
    connect(openFileAction, &QAction::triggered, this, &MainWindow::openFile);

    fileMenu->addSeparator();

    QAction * const saveAction = fileMenu->addAction(QIcon::fromTheme("document-save"), tr("Save"));
    saveAction->setShortcut(QKeySequence::Save);
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveFile);

    QAction * const saveAsAction = fileMenu->addAction(QIcon::fromTheme("document-save-as"), tr("Save as..."));
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::saveFileAs);

    QAction * const saveAllAction = fileMenu->addAction(tr("Save all"));
    connect(saveAllAction, &QAction::triggered, this, &MainWindow::saveAllFiles);

    fileMenu->addSeparator();

    QAction * const closeAction = fileMenu->addAction(QIcon::fromTheme("window-close"), tr("Close"));
    closeAction->setShortcut(QKeySequence::Close);
    connect(closeAction, &QAction::triggered, this, &MainWindow::closeFile);

    QAction * const closeAllAction = fileMenu->addAction(tr("Close All"));
    connect(closeAllAction, &QAction::triggered, this, &MainWindow::closeAllFiles);

    fileMenu->addSeparator();

    QAction * const exitAction = fileMenu->addAction(QIcon::fromTheme("application-exit"), tr("Exit"));
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, this, &MainWindow::close);

    QMenu * const editMenu = menuBar()->addMenu(tr("Edit"));

    QAction * const appendAction = editMenu->addAction(QIcon::fromTheme("list-add"), tr("Append"));
    connect(appendAction, &QAction::triggered, this, &MainWindow::insertItem);

    editMenu->addSeparator();

    QAction * const moveUpAction = editMenu->addAction(QIcon::fromTheme("go-up"), tr("Move up"));
    connect(moveUpAction, &QAction::triggered, this, &MainWindow::moveItemsUp);

    QAction * const moveDownAction = editMenu->addAction(QIcon::fromTheme("go-down"), tr("Move down"));
    connect(moveDownAction, &QAction::triggered, this, &MainWindow::moveItemsDown);

    editMenu->addSeparator();

    QAction * const removeAction = editMenu->addAction(QIcon::fromTheme("list-remove"), tr("Remove"));
    connect(removeAction, &QAction::triggered, this, &MainWindow::removeItems);

    QMenu * const helpMenu = menuBar()->addMenu(tr("Help"));

    QAction * const aboutAction = helpMenu->addAction(QIcon::fromTheme("help-about"), tr("About..."));
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);

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
    if (m_widget->count())
    {
        closeSchemes(schemes(), true);
        event->ignore();
        return;
    }

    event->accept();
}

void MainWindow::newFile()
{
    static int count = 1;
    appendScheme(new SchemeWidget(tr("new-%1.json").arg(count++)));
}

void MainWindow::openFile()
{
    OpenSchemeDialog * const dialog  = new OpenSchemeDialog(this);
    connect(dialog, &OpenSchemeDialog::finished, dialog, &OpenSchemeDialog::deleteLater);
    connect(dialog, &OpenSchemeDialog::filesSelected, this, &MainWindow::openSchemes);

    dialog->open();
}

void MainWindow::saveFile()
{
    SchemeWidget * const scheme = schemeAt(m_widget->currentIndex());
    if (scheme)
        saveSchemes(toList(scheme), false);
}

void MainWindow::saveFileAs()
{
    SchemeWidget * const scheme = schemeAt(m_widget->currentIndex());
    if (scheme)
        saveSchemes(toList(scheme), true);
}

void MainWindow::saveAllFiles()
{
    saveSchemes(schemes(), false);
}

void MainWindow::closeFile()
{
    SchemeWidget * const scheme = schemeAt(m_widget->currentIndex());
    if (scheme)
        closeSchemes(toList(scheme), false);
}

void MainWindow::closeFileByIndex(int index)
{
    closeSchemes(toList(schemeAt(index)), false);
}

void MainWindow::closeAllFiles()
{
    closeSchemes(schemes(), false);
}

void MainWindow::insertItem()
{
    SchemeWidget * const scheme = schemeAt(m_widget->currentIndex());
    if (scheme)
        scheme->insertItem();
}

void MainWindow::removeItems()
{
    SchemeWidget * const scheme = schemeAt(m_widget->currentIndex());
    if (scheme)
        scheme->removeItems();
}

void MainWindow::moveItemsUp()
{
    SchemeWidget * const scheme = schemeAt(m_widget->currentIndex());
    if (scheme)
        scheme->moveItemsUp();
}

void MainWindow::moveItemsDown()
{
    SchemeWidget * const scheme = schemeAt(m_widget->currentIndex());
    if (scheme)
        scheme->moveItemsDown();
}

void MainWindow::about()
{
}

void MainWindow::updateTabHeader(SchemeWidget *scheme)
{
    const QString title = (scheme->isModified() ? tr("%1*") : tr("%1")).arg(scheme->fileName());
    m_widget->setTabText(m_widget->indexOf(scheme), title);

    updateWindowHeader();
}

void MainWindow::updateWindowHeader()
{
    SchemeWidget * const scheme = schemeAt(m_widget->currentIndex());
    setWindowFilePath(scheme ? scheme->fileName() : QString());
    setWindowModified(scheme ? scheme->isModified() : false);
}

void MainWindow::showErrorMessage(const QString &text)
{
    QMessageBox * const box = new QMessageBox(this);
    box->setText(text);
    box->setIcon(QMessageBox::Critical);
    connect(box, &QMessageBox::finished, box, &QMessageBox::deleteLater);

    box->open();
}

void MainWindow::openSchemes(const QStringList &fileNames)
{
    QStringList errors;
    foreach (const QString &fileName, fileNames)
    {
        QScopedPointer<SchemeWidget> scheme(new SchemeWidget(fileName));
        if (scheme->loadFromFile(fileName))
            appendScheme(scheme.take());
        else
            errors.append(fileName);
    }

    if (!errors.isEmpty())
        showErrorMessage(tr("Can't open:\n%1").arg(errors.join("\n")));
}

void MainWindow::querySchemesForSave()
{
    const QList<SchemeWidget *> schemes = m_context.modifiedSchemes();

    if (!schemes.isEmpty())
    {
        SelectSchemeDialog * const dialog = new SelectSchemeDialog(tr("Save files before close?"), schemes, this);
        connect(dialog, &SelectSchemeDialog::finished, dialog, &SelectSchemeDialog::deleteLater);
        connect(dialog, &SelectSchemeDialog::schemesSelected, this, &MainWindow::setSchemesForSave);

        dialog->open();
        return;
    }

    setSchemesForSave(schemes);
}

void MainWindow::setSchemesForSave(const QList<SchemeWidget *> &schemes)
{
    m_context.setSchemesForSave(schemes, false);

    querySchemeFileName();
}

void MainWindow::querySchemeFileName()
{
    SchemeWidget * const scheme = m_context.schemeForSave();
    if (scheme)
    {
        SaveSchemeDialog * const dialog  = new SaveSchemeDialog(scheme->fileName(), this);
        connect(dialog, &SaveSchemeDialog::finished, dialog, &SaveSchemeDialog::deleteLater);
        connect(dialog, &SaveSchemeDialog::fileSelected, this, &MainWindow::setFileName);
        connect(dialog, &SaveSchemeDialog::accepted, this, &MainWindow::querySchemeFileName);

        dialog->open();
        return;
    }

    saveThenCloseSchemes();
}

void MainWindow::setFileName(const QString &fileName)
{
    m_context.schemesForSave[m_context.schemeForSave()] = fileName;
}

void MainWindow::saveThenCloseSchemes()
{
    QStringList errors;
    foreach (SchemeWidget *scheme, m_context.schemesForSave.keys())
    {
        const QString fileName = m_context.schemesForSave.value(scheme);
        if (!scheme->saveToFile(fileName))
        {
            m_context.schemesForClose.removeAll(scheme);
            errors.append(fileName);
        }
    }

    foreach (SchemeWidget *scheme, m_context.schemesForClose)
        scheme->deleteLater();

    if (!errors.isEmpty())
    {
        showErrorMessage(tr("Can't save:\n%1").arg(errors.join("\n")));
        return;
    }

    if (m_context.exitAfterClose)
        emit closeRequested();
}

void MainWindow::appendScheme(SchemeWidget *scheme)
{
    m_widget->addTab(scheme, QIcon::fromTheme("text-x-generic"), QString());
    connect(scheme, &SchemeWidget::statusChanged, this, &MainWindow::updateTabHeader);
    updateTabHeader(scheme);
}

void MainWindow::saveSchemes(const QList<SchemeWidget *> &schemes, bool askFileName)
{
    m_context = SaveCloseContext();
    m_context.setSchemesForSave(schemes, askFileName);

    querySchemeFileName();
}

void MainWindow::closeSchemes(const QList<SchemeWidget *> &schemes, bool exitAfterClose)
{
    m_context = SaveCloseContext();
    m_context.schemesForClose = schemes;
    m_context.exitAfterClose = exitAfterClose;

    querySchemesForSave();
}

QList<SchemeWidget *> MainWindow::schemes() const
{
    QList<SchemeWidget *> schemes;
    for (int index = 0; index < m_widget->count(); index++)
        schemes.append(schemeAt(index));

    return schemes;
}

SchemeWidget *MainWindow::schemeAt(int index) const
{
    return qobject_cast<SchemeWidget *>(m_widget->widget(index));
}


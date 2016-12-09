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
#include "PickSchemeDialog.h"

template<typename T>
static QList<T> toList(T value)
{
    QList<T> result;
    result.append(value);

    return result;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_widget(new QTabWidget),
      m_askFileName(false),
      m_exitAfterClose(false)
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

    QAction * const insertAction = editMenu->addAction(QIcon::fromTheme("list-add"), tr("Add"));
    connect(insertAction, &QAction::triggered, this, &MainWindow::insertEntry);

    editMenu->addSeparator();

    QAction * const moveToTopAction = editMenu->addAction(QIcon::fromTheme("go-top"), tr("Move to top"));
    connect(moveToTopAction, &QAction::triggered, this, &MainWindow::moveEntriesToTop);

    QAction * const moveUpAction = editMenu->addAction(QIcon::fromTheme("go-up"), tr("Move up"));
    connect(moveUpAction, &QAction::triggered, this, &MainWindow::moveEntriesUp);

    QAction * const moveDownAction = editMenu->addAction(QIcon::fromTheme("go-down"), tr("Move down"));
    connect(moveDownAction, &QAction::triggered, this, &MainWindow::moveEntriesDown);

    QAction * const moveToBottomAction = editMenu->addAction(QIcon::fromTheme("go-bottom"), tr("Move to bottom"));
    connect(moveToBottomAction, &QAction::triggered, this, &MainWindow::moveEntriesToBottom);

    editMenu->addSeparator();

    QAction * const removeAction = editMenu->addAction(QIcon::fromTheme("list-remove"), tr("Remove"));
    connect(removeAction, &QAction::triggered, this, &MainWindow::removeEntries);

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
    if (!allSchemes().isEmpty())
    {
        event->ignore();
        closeSchemes(allSchemes(), true);
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
    OpenSchemeDialog * const dialog  = new OpenSchemeDialog(window());
    connect(dialog, &OpenSchemeDialog::finished, dialog, &OpenSchemeDialog::deleteLater);
    connect(dialog, &OpenSchemeDialog::filesSelected, this, &MainWindow::openSchemes);

    dialog->open();
}

void MainWindow::saveFile()
{
    SchemeWidget * const scheme = schemeByIndex(m_widget->currentIndex());
    if (scheme)
        saveSchemes(toList(scheme), false);
}

void MainWindow::saveFileAs()
{
    SchemeWidget * const scheme = schemeByIndex(m_widget->currentIndex());
    if (scheme)
        saveSchemes(toList(scheme), true);
}

void MainWindow::saveAllFiles()
{
    saveSchemes(allSchemes(), false);
}

void MainWindow::closeFile()
{
    SchemeWidget * const scheme = schemeByIndex(m_widget->currentIndex());
    if (scheme)
        closeSchemes(toList(scheme), false);
}

void MainWindow::closeFileByIndex(int index)
{
    closeSchemes(toList(schemeByIndex(index)), false);
}

void MainWindow::closeAllFiles()
{
    closeSchemes(allSchemes(), false);
}

void MainWindow::insertEntry()
{
    SchemeWidget * const scheme = schemeByIndex(m_widget->currentIndex());
    if (scheme)
        scheme->insertEntry();
}

void MainWindow::removeEntries()
{
    SchemeWidget * const scheme = schemeByIndex(m_widget->currentIndex());
    if (scheme)
        scheme->removeEntries();
}

void MainWindow::moveEntriesToTop()
{
    SchemeWidget * const scheme = schemeByIndex(m_widget->currentIndex());
    if (scheme)
        scheme->moveEntries(SchemeWidget::MoveToTop);
}

void MainWindow::moveEntriesUp()
{
    SchemeWidget * const scheme = schemeByIndex(m_widget->currentIndex());
    if (scheme)
        scheme->moveEntries(SchemeWidget::MoveUp);
}

void MainWindow::moveEntriesDown()
{
    SchemeWidget * const scheme = schemeByIndex(m_widget->currentIndex());
    if (scheme)
        scheme->moveEntries(SchemeWidget::MoveDown);
}

void MainWindow::moveEntriesToBottom()
{
    SchemeWidget * const scheme = schemeByIndex(m_widget->currentIndex());
    if (scheme)
        scheme->moveEntries(SchemeWidget::MoveToBottom);
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
    SchemeWidget * const scheme = schemeByIndex(m_widget->currentIndex());
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
    QList<SchemeWidget *> modified;
    foreach (SchemeWidget *scheme, m_schemesForClose)
    {
        if (scheme->isModified())
            modified.append(scheme);
    }

    if (!modified.isEmpty())
    {
        PickSchemeDialog * const dialog = new PickSchemeDialog(tr("Save files before close?"), modified, this);
        connect(dialog, &PickSchemeDialog::finished, dialog, &PickSchemeDialog::deleteLater);
        connect(dialog, &PickSchemeDialog::schemesSelected, this, &MainWindow::setSchemesForSave);

        dialog->open();
        return;
    }

    setSchemesForSave(modified);
}

void MainWindow::setSchemesForSave(const QList<SchemeWidget *> &schemes)
{
    m_schemesForSave = schemes;

    querySchemeFileName();
}

void MainWindow::querySchemeFileName()
{
    while (!m_schemesForSave.isEmpty())
    {
        const SchemeWidget *scheme = m_schemesForSave.first();
        if (scheme->isNew() || m_askFileName)
        {
            SaveSchemeDialog * const dialog  = new SaveSchemeDialog(scheme->fileName(), this);
            connect(dialog, &SaveSchemeDialog::finished, dialog, &SaveSchemeDialog::deleteLater);
            connect(dialog, &SaveSchemeDialog::fileSelected, this, &MainWindow::setSchemeFileName);
            connect(dialog, &SaveSchemeDialog::accepted, this, &MainWindow::querySchemeFileName);

            dialog->open();
            return;
        }

        setSchemeFileName(scheme->fileName());
    }

    saveThenCloseSchemes();
}

void MainWindow::setSchemeFileName(const QString &fileName)
{
    m_schemes.insert(m_schemesForSave.takeFirst(), fileName);
}

void MainWindow::saveThenCloseSchemes()
{
    QStringList errors;
    foreach (SchemeWidget *scheme, m_schemes.keys())
    {
        const QString fileName = m_schemes.value(scheme);
        if (!scheme->saveToFile(fileName))
        {
            m_schemesForClose.removeAll(scheme);
            errors.append(fileName);
        }
    }

    foreach (SchemeWidget *scheme, m_schemesForClose)
        scheme->deleteLater();

    if (!errors.isEmpty())
    {
        showErrorMessage(tr("Can't save:\n%1").arg(errors.join("\n")));
        return;
    }

    if (m_exitAfterClose)
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
    m_schemesForClose.clear();
    m_schemesForSave = schemes;
    m_schemes.clear();
    m_askFileName = askFileName;
    m_exitAfterClose = false;

    querySchemeFileName();
}

void MainWindow::closeSchemes(const QList<SchemeWidget *> &schemes, bool exitAfterClose)
{
    m_schemesForClose = schemes;
    m_schemesForSave.clear();
    m_schemes.clear();
    m_askFileName = false;
    m_exitAfterClose = exitAfterClose;

    querySchemesForSave();
}

QList<SchemeWidget *> MainWindow::allSchemes() const
{
    QList<SchemeWidget *> schemes;
    for (int index = 0; index < m_widget->count(); index++)
        schemes.append(schemeByIndex(index));

    return schemes;
}

SchemeWidget *MainWindow::schemeByIndex(int index) const
{
    return qobject_cast<SchemeWidget *>(m_widget->widget(index));
}

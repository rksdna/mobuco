#include <QMenu>
#include <QDebug>
#include <QMenuBar>
#include <QSettings>
#include <QTabWidget>
#include <QMessageBox>
#include <QCloseEvent>
#include <QApplication>
#include "MainWindow.h"
#include "ScheduleWidget.h"
#include "SaveScheduleDialog.h"
#include "OpenScheduleDialog.h"
#include "PickScheduleDialog.h"

template<typename T>
static QList<T> toList(T item)
{
    QList<T> items;
    items.append(item);

    return items;
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
    if (!allItems().isEmpty())
    {
        event->ignore();
        closeItems(allItems(), true);
        return;
    }

    event->accept();
}

void MainWindow::newFile()
{
    static int count = 1;
    appendItem(new ScheduleWidget(tr("new-%1.json").arg(count++)));
}

void MainWindow::openFile()
{
    OpenScheduleDialog * const dialog  = new OpenScheduleDialog(window());
    connect(dialog, &OpenScheduleDialog::finished, dialog, &OpenScheduleDialog::deleteLater);
    connect(dialog, &OpenScheduleDialog::filesSelected, this, &MainWindow::openItems);

    dialog->open();
}

void MainWindow::saveFile()
{
    ScheduleWidget * const item = itemByIndex(m_widget->currentIndex());
    if (item)
        saveItems(toList(item), false);
}

void MainWindow::saveFileAs()
{
    ScheduleWidget * const item = itemByIndex(m_widget->currentIndex());
    if (item)
        saveItems(toList(item), true);
}

void MainWindow::saveAllFiles()
{
    saveItems(allItems(), false);
}

void MainWindow::closeFile()
{
    ScheduleWidget * const item = itemByIndex(m_widget->currentIndex());
    if (item)
        closeItems(toList(item), false);
}

void MainWindow::closeFileByIndex(int index)
{
    closeItems(toList(itemByIndex(index)), false);
}

void MainWindow::closeAllFiles()
{
    closeItems(allItems(), false);
}

void MainWindow::insertEntry()
{
    ScheduleWidget * const item = itemByIndex(m_widget->currentIndex());
    if (item)
        item->insertEntry();
}

void MainWindow::removeEntries()
{
    ScheduleWidget * const item = itemByIndex(m_widget->currentIndex());
    if (item)
        item->removeEntries();
}

void MainWindow::moveEntriesToTop()
{
    ScheduleWidget * const item = itemByIndex(m_widget->currentIndex());
    if (item)
        item->moveEntries(ScheduleWidget::MoveToTop);
}

void MainWindow::moveEntriesUp()
{
    ScheduleWidget * const item = itemByIndex(m_widget->currentIndex());
    if (item)
        item->moveEntries(ScheduleWidget::MoveUp);
}

void MainWindow::moveEntriesDown()
{
    ScheduleWidget * const item = itemByIndex(m_widget->currentIndex());
    if (item)
        item->moveEntries(ScheduleWidget::MoveDown);
}

void MainWindow::moveEntriesToBottom()
{
    ScheduleWidget * const item = itemByIndex(m_widget->currentIndex());
    if (item)
        item->moveEntries(ScheduleWidget::MoveToBottom);
}

void MainWindow::about()
{
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

void MainWindow::showErrorMessage(const QString &text)
{
    QMessageBox * const box = new QMessageBox(this);
    box->setText(text);
    box->setIcon(QMessageBox::Critical);
    connect(box, &QMessageBox::finished, box, &QMessageBox::deleteLater);

    box->open();
}

void MainWindow::openItems(const QStringList &fileNames)
{
    QStringList errors;
    foreach (const QString &fileName, fileNames)
    {
        QScopedPointer<ScheduleWidget> item(new ScheduleWidget(fileName));
        if (item->loadFromFile(fileName))
            appendItem(item.take());
        else
            errors.append(fileName);
    }

    if (!errors.isEmpty())
        showErrorMessage(tr("Can't open:\n%1").arg(errors.join("\n")));
}

void MainWindow::queryItemsForSave()
{
    QList<ScheduleWidget *> modified;
    foreach (ScheduleWidget *item, m_itemsForClose)
    {
        if (item->isModified())
            modified.append(item);
    }

    if (!modified.isEmpty())
    {
        PickScheduleDialog * const dialog = new PickScheduleDialog(tr("Save files before close?"), modified, this);
        connect(dialog, &PickScheduleDialog::finished, dialog, &PickScheduleDialog::deleteLater);
        connect(dialog, &PickScheduleDialog::itemsSelected, this, &MainWindow::setItemsForSave);

        dialog->open();
        return;
    }

    setItemsForSave(modified);
}

void MainWindow::setItemsForSave(const QList<ScheduleWidget *> &items)
{
    m_itemsForSave = items;

    queryItemFileName();
}

void MainWindow::queryItemFileName()
{
    while (!m_itemsForSave.isEmpty())
    {
        const ScheduleWidget *item = m_itemsForSave.first();
        if (item->isNew() || m_askFileName)
        {
            SaveScheduleDialog * const dialog  = new SaveScheduleDialog(item->fileName(), this);
            connect(dialog, &SaveScheduleDialog::finished, dialog, &SaveScheduleDialog::deleteLater);
            connect(dialog, &SaveScheduleDialog::fileSelected, this, &MainWindow::setItemFileName);
            connect(dialog, &SaveScheduleDialog::accepted, this, &MainWindow::queryItemFileName);

            dialog->open();
            return;
        }

        setItemFileName(item->fileName());
    }

    saveThenCloseItems();
}

void MainWindow::setItemFileName(const QString &fileName)
{
    m_items.insert(m_itemsForSave.takeFirst(), fileName);
}

void MainWindow::saveThenCloseItems()
{
    QStringList errors;
    foreach (ScheduleWidget *item, m_items.keys())
    {
        const QString fileName = m_items.value(item);
        if (!item->saveToFile(fileName))
        {
            m_itemsForClose.removeAll(item);
            errors.append(fileName);
        }
    }

    foreach (ScheduleWidget *item, m_itemsForClose)
        item->deleteLater();

    if (!errors.isEmpty())
    {
        showErrorMessage(tr("Can't save:\n%1").arg(errors.join("\n")));
        return;
    }

    if (m_exitAfterClose)
        emit closeRequested();
}

void MainWindow::appendItem(ScheduleWidget *item)
{
    m_widget->addTab(item, QIcon::fromTheme("text-x-generic"), QString());
    connect(item, &ScheduleWidget::statusChanged, this, &MainWindow::updateTabHeader);
    updateTabHeader(item);
}

void MainWindow::saveItems(const QList<ScheduleWidget *> &items, bool askFileName)
{
    m_itemsForClose.clear();
    m_itemsForSave = items;
    m_items.clear();
    m_askFileName = askFileName;
    m_exitAfterClose = false;

    queryItemFileName();
}

void MainWindow::closeItems(const QList<ScheduleWidget *> &items, bool exitAfterClose)
{
    m_itemsForClose = items;
    m_itemsForSave.clear();
    m_items.clear();
    m_askFileName = false;
    m_exitAfterClose = exitAfterClose;

    queryItemsForSave();
}

QList<ScheduleWidget *> MainWindow::allItems() const
{
    QList<ScheduleWidget *> items;
    for (int index = 0; index < m_widget->count(); index++)
        items.append(itemByIndex(index));

    return items;
}

ScheduleWidget *MainWindow::itemByIndex(int index) const
{
    return qobject_cast<ScheduleWidget *>(m_widget->widget(index));
}

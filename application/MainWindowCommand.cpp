#include <QDebug>
#include <QMessageBox>
#include "MainWindow.h"
#include "ScheduleWidget.h"
#include "MainWindowCommand.h"
#include "OpenScheduleDialog.h"
#include "SaveScheduleDialog.h"
#include "PickScheduleDialog.h"

Command::Command(MainWindow *parent)
    : QObject(parent),
      m_window(parent)
{
    connect(this, &Command::completed, this, &Command::deleteLater);
    connect(this, &Command::aborted, this, &Command::deleteLater);

    qDebug() << "Hello" << this;
}

Command::~Command()
{
    qDebug() << "Bue" << this;
}

MainWindow *Command::window() const
{
    return m_window;
}

void Command::showErrorMessage(const QString &text)
{
    QMessageBox * const box = new QMessageBox(window());
    box->setText(text);
    box->setIcon(QMessageBox::Critical);
    connect(box, &QMessageBox::finished, box, &QMessageBox::deleteLater);

    box->open();
}

NewCommand::NewCommand(MainWindow *parent)
    : Command(parent)
{
}

void NewCommand::execute()
{
    static int count = 1;
    window()->appendItem(new ScheduleWidget(tr("new%1").arg(count++)));

    emit completed();
}

OpenCommand::OpenCommand(MainWindow *parent)
    : Command(parent)
{
}

void OpenCommand::execute()
{
    OpenScheduleDialog * const dialog  = new OpenScheduleDialog(window());
    connect(dialog, &OpenScheduleDialog::finished, dialog, &OpenScheduleDialog::deleteLater);
    connect(dialog, &OpenScheduleDialog::rejected, this, &OpenCommand::aborted);
    connect(dialog, &OpenScheduleDialog::filesSelected, this, &OpenCommand::process);

    dialog->open();
}

void OpenCommand::process(const QStringList &fileNames)
{
    QStringList errors;
    foreach (const QString &fileName, fileNames)
    {
        QScopedPointer<ScheduleWidget> item(new ScheduleWidget(fileName));
        if (item->loadFromFile(fileName))
            window()->appendItem(item.take());
        else
            errors.append(fileName);
    }

    if (!errors.isEmpty())
    {
        showErrorMessage(tr("Can't open:\n%1").arg(errors.join("\n")));
        emit aborted();
        return;
    }

    emit completed();
}

SaveCommand::SaveCommand(const QList<ScheduleWidget *> &items, MainWindow *parent)
    : Command(parent),
      m_askFileName(false),
      m_items(items)
{
}

void SaveCommand::setAskFileName(bool askFileName)
{
    m_askFileName = askFileName;
}

void SaveCommand::execute()
{
    while (!m_items.isEmpty())
    {
        ScheduleWidget * const item = m_items.first();
        if (m_askFileName || item->isNew())
        {
            SaveScheduleDialog * const dialog  = new SaveScheduleDialog(item->fileName(), window());
            connect(dialog, &OpenScheduleDialog::finished, dialog, &OpenScheduleDialog::deleteLater);
            connect(dialog, &OpenScheduleDialog::rejected, this, &OpenCommand::aborted);
            connect(dialog, &OpenScheduleDialog::fileSelected, this, &SaveCommand::process);
            connect(dialog, &OpenScheduleDialog::accepted, this, &SaveCommand::execute);

            dialog->open();
            return;
        }

        process(item->fileName());
    }

    if (!m_errors.isEmpty())
    {
        showErrorMessage(tr("Can't save:\n%1").arg(m_errors.join("\n")));
        emit aborted();
        return;
    }

    emit completed();
}

void SaveCommand::process(const QString &fileName)
{
    ScheduleWidget * const item = m_items.takeFirst();
    if (item->saveToFile(fileName))
        emit itemSaved(item);
    else
        m_errors.append(fileName);
}

CloseCommand::CloseCommand(const QList<ScheduleWidget *> &items, MainWindow *parent)
    : Command(parent),
      m_items(items)
{
}

void CloseCommand::execute()
{
    QList<ScheduleWidget *> modified;
    foreach (ScheduleWidget *item, m_items)
    {
        if (item->isModified())
            modified.append(item);
    }

    if (!modified.isEmpty())
    {
        PickScheduleDialog * const dialog = new PickScheduleDialog(tr("Save files before close?"), modified, window());
        connect(dialog, &PickScheduleDialog::finished, dialog, &PickScheduleDialog::deleteLater);
        connect(dialog, &OpenScheduleDialog::rejected, this, &CloseCommand::aborted);
        connect(dialog, &PickScheduleDialog::itemsSelected, this, &CloseCommand::process);

        dialog->open();
        return;
    }

    process(modified);
}

void CloseCommand::process(const QList<ScheduleWidget *> &items)
{
    foreach (ScheduleWidget *item, m_items)
    {
        if (!items.contains(item))
            window()->removeItem(item);
    }

    SaveCommand * const command = new SaveCommand(items, window());
    connect(command, &SaveCommand::itemSaved, this, &CloseCommand::closeItem);
    connect(command, &SaveCommand::completed, this, &CloseCommand::completed);
    connect(command, &SaveCommand::aborted, this, &CloseCommand::aborted);

    command->execute();
}

void CloseCommand::closeItem(ScheduleWidget *item)
{
    window()->removeItem(item);
}

#include "MainWindow.h"
#include "SaveCommand.h"
#include "ScheduleWidget.h"
#include "SaveScheduleDialog.h"

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
            connect(dialog, &SaveScheduleDialog::finished, dialog, &SaveScheduleDialog::deleteLater);
            connect(dialog, &SaveScheduleDialog::rejected, this, &SaveCommand::aborted);
            connect(dialog, &SaveScheduleDialog::fileSelected, this, &SaveCommand::process);
            connect(dialog, &SaveScheduleDialog::accepted, this, &SaveCommand::execute);

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

#include "MainWindow.h"
#include "SaveCommand.h"
#include "CloseCommand.h"
#include "ScheduleWidget.h"
#include "PickScheduleDialog.h"

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
        connect(dialog, &PickScheduleDialog::rejected, this, &CloseCommand::aborted);
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


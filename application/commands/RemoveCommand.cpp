#include "RemoveCommand.h"
#include "ScheduleWidget.h"

RemoveCommand::RemoveCommand(ScheduleWidget *item, MainWindow *parent)
    : Command(parent),
      m_item(item)
{
}

void RemoveCommand::execute()
{
    if (!m_item)
    {
        emit aborted();
        return;
    }

    m_item->removeEntries();
    emit completed();
}

#include "InsertCommand.h"
#include "ScheduleWidget.h"

InsertCommand::InsertCommand(ScheduleWidget *item, MainWindow *parent)
    : Command(parent),
      m_item(item)
{
}

void InsertCommand::execute()
{
    if (!m_item)
    {
        emit aborted();
        return;
    }

    m_item->insertEntry();
    emit completed();
}

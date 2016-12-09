#include "MoveCommand.h"

MoveCommand::MoveCommand(ScheduleWidget *item, ScheduleWidget::Move move, MainWindow *parent)
    : Command(parent),
      m_item(item),
      m_move(move)
{
}

void MoveCommand::execute()
{
    if (!m_item)
    {
        emit aborted();
        return;
    }

    m_item->moveEntries(m_move);
    emit completed();
}


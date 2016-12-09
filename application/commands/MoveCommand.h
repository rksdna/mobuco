#ifndef MOVECOMMAND_H
#define MOVECOMMAND_H

#include "Command.h"
#include "ScheduleWidget.h"

class MoveCommand : public Command
{
public:
    MoveCommand(ScheduleWidget *item, ScheduleWidget::Move move, MainWindow *parent);
    void execute();

private:
    ScheduleWidget * const m_item;
    const ScheduleWidget::Move m_move;
};

#endif // MOVECOMMAND_H

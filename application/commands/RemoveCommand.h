#ifndef REMOVECOMMAND_H
#define REMOVECOMMAND_H

#include "Command.h"

class ScheduleWidget;

class RemoveCommand : public Command
{
    Q_OBJECT
public:
    RemoveCommand(ScheduleWidget *item, MainWindow *parent);
    void execute();

private:
    ScheduleWidget * const m_item;
};

#endif // REMOVECOMMAND_H

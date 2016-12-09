#ifndef INSERTCOMMAND_H
#define INSERTCOMMAND_H

#include "Command.h"

class ScheduleWidget;

class InsertCommand : public Command
{
    Q_OBJECT
public:
    InsertCommand(ScheduleWidget *item, MainWindow *parent);
    void execute();

private:
    ScheduleWidget * const m_item;
};

#endif // INSERTCOMMAND_H

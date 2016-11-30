#ifndef CLOSECOMMAND_H
#define CLOSECOMMAND_H

#include <QList>
#include "Command.h"

class CloseCommand : public Command
{
    Q_OBJECT
public:
    CloseCommand(const QList<ScheduleWidget *> &items, MainWindow *parent);
    void execute();

private slots:
    void process(const QList<ScheduleWidget *> &items);
    void closeItem(ScheduleWidget *item);

private:
    QList<ScheduleWidget *> m_items;
};

#endif // CLOSECOMMAND_H

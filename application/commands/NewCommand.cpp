#include "NewCommand.h"
#include "MainWindow.h"
#include "ScheduleWidget.h"

NewCommand::NewCommand(MainWindow *parent)
    : Command(parent)
{
}

void NewCommand::execute()
{
    static int count = 1;
    window()->appendItem(new ScheduleWidget(tr("new-%1.json").arg(count++)));

    emit completed();
}

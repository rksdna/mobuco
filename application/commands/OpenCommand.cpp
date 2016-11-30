#include "MainWindow.h"
#include "OpenCommand.h"
#include "ScheduleWidget.h"
#include "OpenScheduleDialog.h"

OpenCommand::OpenCommand(MainWindow *parent)
    : Command(parent)
{
}

void OpenCommand::execute()
{
    OpenScheduleDialog * const dialog  = new OpenScheduleDialog(window());
    connect(dialog, &OpenScheduleDialog::finished, dialog, &OpenScheduleDialog::deleteLater);
    connect(dialog, &OpenScheduleDialog::rejected, this, &OpenCommand::aborted);
    connect(dialog, &OpenScheduleDialog::filesSelected, this, &OpenCommand::process);

    dialog->open();
}

void OpenCommand::process(const QStringList &fileNames)
{
    QStringList errors;
    foreach (const QString &fileName, fileNames)
    {
        QScopedPointer<ScheduleWidget> item(new ScheduleWidget(fileName));
        if (item->loadFromFile(fileName))
            window()->appendItem(item.take());
        else
            errors.append(fileName);
    }

    if (!errors.isEmpty())
    {
        showErrorMessage(tr("Can't open:\n%1").arg(errors.join("\n")));
        emit aborted();
        return;
    }

    emit completed();
}

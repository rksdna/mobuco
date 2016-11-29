#include <QSettings>
#include "OpenScheduleDialog.h"

OpenScheduleDialog::OpenScheduleDialog(QWidget *parent)
    : QFileDialog(parent)
{
    setAcceptMode(QFileDialog::AcceptOpen);
    setFileMode(QFileDialog::ExistingFiles);
    setNameFilter(tr("JSON files (*.json)\nAny files (*)"));

    QSettings settings;
    restoreGeometry(settings.value("OpenScheduleDialog/Geometry").toByteArray());
    restoreState(settings.value("OpenScheduleDialog/State").toByteArray());
}

void OpenScheduleDialog::hideEvent(QHideEvent *event)
{
    QSettings settings;
    settings.setValue("OpenScheduleDialog/Geometry", saveGeometry());
    settings.setValue("OpenScheduleDialog/State", saveState());

    QFileDialog::hideEvent(event);
}

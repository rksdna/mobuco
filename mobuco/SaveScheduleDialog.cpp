#include <QSettings>
#include "SaveScheduleDialog.h"

SaveScheduleDialog::SaveScheduleDialog(const QString &fileName, QWidget *parent)
    : QFileDialog(parent)
{
    setAcceptMode(QFileDialog::AcceptSave);
    setFileMode(QFileDialog::AnyFile);
    setNameFilter(tr("JSON files (*.json)"));
    setDefaultSuffix("json");
    selectFile(fileName);

    QSettings settings;
    restoreGeometry(settings.value("SaveScheduleDialog/Geometry").toByteArray());
    restoreState(settings.value("SaveScheduleDialog/State").toByteArray());
}

void SaveScheduleDialog::hideEvent(QHideEvent *event)
{
    QSettings settings;
    settings.setValue("SaveScheduleDialog/Geometry", saveGeometry());
    settings.setValue("SaveScheduleDialog/State", saveState());

    QFileDialog::hideEvent(event);
}

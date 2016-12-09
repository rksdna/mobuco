#include <QSettings>
#include "OpenSchemeDialog.h"

OpenSchemeDialog::OpenSchemeDialog(QWidget *parent)
    : QFileDialog(parent)
{
    setAcceptMode(QFileDialog::AcceptOpen);
    setFileMode(QFileDialog::ExistingFiles);
    setNameFilter(tr("JSON files (*.json)\nAny files (*)"));

    QSettings settings;
    restoreGeometry(settings.value("OpenSchemeDialog/Geometry").toByteArray());
    restoreState(settings.value("OpenSchemeDialog/State").toByteArray());
}

void OpenSchemeDialog::hideEvent(QHideEvent *event)
{
    QSettings settings;
    settings.setValue("OpenSchemeDialog/Geometry", saveGeometry());
    settings.setValue("OpenSchemeDialog/State", saveState());

    QFileDialog::hideEvent(event);
}

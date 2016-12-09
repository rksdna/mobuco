#include <QSettings>
#include "SaveSchemeDialog.h"

SaveSchemeDialog::SaveSchemeDialog(const QString &fileName, QWidget *parent)
    : QFileDialog(parent)
{
    setAcceptMode(QFileDialog::AcceptSave);
    setFileMode(QFileDialog::AnyFile);
    setNameFilter(tr("JSON files (*.json)"));
    setDefaultSuffix("json");
    selectFile(fileName);

    QSettings settings;
    restoreGeometry(settings.value("SaveSchemeDialog/Geometry").toByteArray());
    restoreState(settings.value("SaveSchemeDialog/State").toByteArray());
}

void SaveSchemeDialog::hideEvent(QHideEvent *event)
{
    QSettings settings;
    settings.setValue("SaveSchemeDialog/Geometry", saveGeometry());
    settings.setValue("SaveSchemeDialog/State", saveState());

    QFileDialog::hideEvent(event);
}

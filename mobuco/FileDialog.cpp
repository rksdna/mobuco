#include <QSettings>
#include "FileDialog.h"

FileDialog::FileDialog(Operation operation, QWidget *parent)
    : QFileDialog(parent)
{
    connect(this, &FileDialog::finished, this, &FileDialog::deleteLater);

    switch (operation)
    {
    case OpenFiles:
        setAcceptMode(QFileDialog::AcceptOpen);
        setFileMode(QFileDialog::ExistingFiles);
        setNameFilter(tr("JSON files (*.json)\nAny files (*)"));
        break;

    case SaveFile:
        setAcceptMode(QFileDialog::AcceptSave);
        setFileMode(QFileDialog::AnyFile);
        setNameFilter(tr("JSON files (*.json)"));
        setDefaultSuffix("json");
        break;

    default:
        break;
    }

    QSettings settings;
    restoreGeometry(settings.value("FileDialog/Geometry").toByteArray());
    restoreState(settings.value("FileDialog/State").toByteArray());
}

void FileDialog::hideEvent(QHideEvent *event)
{
    QSettings settings;
    settings.setValue("FileDialog/Geometry", saveGeometry());
    settings.setValue("FileDialog/State", saveState());

    QFileDialog::hideEvent(event);
}

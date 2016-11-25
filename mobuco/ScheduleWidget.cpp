#include <QFileInfo>
#include <QBoxLayout>
#include <QPushButton>
#include "ScheduleWidget.h"

ScheduleWidget::ScheduleWidget(QWidget *parent)
    : QWidget(parent)
{
    _modified = false;

    QPushButton * const touchButton = new QPushButton("Touch");
    connect(touchButton, &QPushButton::clicked, this, &ScheduleWidget::touch);

    QBoxLayout * const layout = new QVBoxLayout(this);
    layout->addWidget(touchButton);
}

QString ScheduleWidget::fileName() const
{
    return _fileName;
}

bool ScheduleWidget::isModified() const
{
    return _modified;
}

void ScheduleWidget::createNew()
{
    setFileState("new.json", false);
}

bool ScheduleWidget::loadFromFile(const QString &fileName)
{
    setFileState(fileName, false);
    return true;
}

bool ScheduleWidget::saveToFile(const QString &fileName)
{
    setFileState(fileName, false);
    return true;
}

void ScheduleWidget::touch()
{
    setFileState(fileName(), !isModified());
}

void ScheduleWidget::setFileState(const QString &fileName, bool m)
{
    _fileName = fileName;
    _modified = m;
    emit modified(this);
}

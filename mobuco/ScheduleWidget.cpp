#include <QDebug>
#include <QFileInfo>
#include <QBoxLayout>
#include <QPushButton>
#include "ScheduleWidget.h"

ScheduleWidget::ScheduleWidget(QWidget *parent)
    : QWidget(parent)
{
    _allocated = false;
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

bool ScheduleWidget::isNew() const
{
    return _allocated;
}

bool ScheduleWidget::isModified() const
{
    return _modified;
}

void ScheduleWidget::createNew(const QString &fileName)
{
    setFileState(fileName, true, false);
}

bool ScheduleWidget::loadFromFile(const QString &fileName)
{
    setFileState(fileName, false, false);
    return false;
}

bool ScheduleWidget::saveToFile(const QString &fileName)
{
    qDebug() << "Save" << fileName;
    setFileState(fileName, false, false);
    return true;
}

void ScheduleWidget::touch()
{
    setFileState(fileName(), isNew(), !isModified());
}

void ScheduleWidget::setFileState(const QString &fileName, bool a, bool m)
{
    _fileName = fileName;
    _allocated = a;
    _modified = m;
    emit modified(this);
}

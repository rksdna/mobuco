#include <QDebug>
#include <QBoxLayout>
#include <QPushButton>
#include "ScheduleWidget.h"

ScheduleWidget::ScheduleWidget(const QString &fileName, QWidget *parent)
    : QWidget(parent),
      m_fileName(fileName),
      m_isNew(true),
      m_isModified(false)
{
    QPushButton * const touchButton = new QPushButton(tr("Touch"));
    connect(touchButton, &QPushButton::clicked, this, &ScheduleWidget::touch);

    QBoxLayout * const layout = new QVBoxLayout(this);
    layout->addWidget(touchButton);
}

QString ScheduleWidget::fileName() const
{
    return m_fileName;
}

bool ScheduleWidget::isNew() const
{
    return m_isNew;
}

bool ScheduleWidget::isModified() const
{
    return m_isModified;
}

bool ScheduleWidget::loadFromFile(const QString &fileName)
{
    qDebug() << Q_FUNC_INFO << fileName;
    setStatus(fileName, false, false);
    return qrand() % 2;
}

bool ScheduleWidget::saveToFile(const QString &fileName)
{
    qDebug() << Q_FUNC_INFO << fileName;
    setStatus(fileName, false, false);
    return qrand() % 2;
}

void ScheduleWidget::touch()
{
    setStatus(fileName(), isNew(), true);
}

void ScheduleWidget::setStatus(const QString &fileName, bool isNew, bool isModified)
{
    m_fileName = fileName;
    m_isNew = isNew;
    m_isModified = isModified;
    emit statusChanged(this);
}

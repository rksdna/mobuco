#include <QFile>
#include <QSaveFile>
#include <QBoxLayout>
#include <QTableView>
#include <QHeaderView>
#include <QJsonDocument>
#include "ScheduleModel.h"
#include "ScheduleWidget.h"
#include "ScheduleDelegate.h"

ScheduleWidget::ScheduleWidget(const QString &fileName, QWidget *parent)
    : QWidget(parent),
      m_model(new ScheduleModel(this)),
      m_view(new QTableView),
      m_fileName(fileName),
      m_isNew(true),
      m_isModified(false)
{
    connect(m_model, &ScheduleModel::dataChanged, this, &ScheduleWidget::changeStatus);
    connect(m_model, &ScheduleModel::rowsInserted, this, &ScheduleWidget::changeStatus);
    connect(m_model, &ScheduleModel::rowsRemoved, this, &ScheduleWidget::changeStatus);
    connect(m_model, &ScheduleModel::rowsMoved, this, &ScheduleWidget::changeStatus);

    m_view->setItemDelegate(new ScheduleDelegate(this));
    m_view->setSelectionMode(QTableView::SingleSelection);
    m_view->setSelectionBehavior(QTableView::SelectRows);
    m_view->horizontalHeader()->setHighlightSections(false);
    m_view->horizontalHeader()->setStretchLastSection(true);
    m_view->setAlternatingRowColors(true);
    m_view->setModel(m_model);

    QBoxLayout * const layout = new QVBoxLayout(this);
    layout->addWidget(m_view);
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
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
        return false;

    QJsonParseError error;
    const QJsonDocument document = QJsonDocument::fromJson(file.readAll(), &error);
    if (error.error != QJsonParseError::NoError)
        return false;

    m_model->readFromJson(document);
    setStatus(fileName, false, false);
    return true;
}

bool ScheduleWidget::saveToFile(const QString &fileName)
{
    QSaveFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
        return false;

    const QJsonDocument document = m_model->writeToJson();
    file.write(document.toJson());
    if (!file.commit())
        return false;

    setStatus(fileName, false, false);
    return true;
}

void ScheduleWidget::changeStatus()
{
    setStatus(m_fileName, m_isNew, true);
}

void ScheduleWidget::setStatus(const QString &fileName, bool isNew, bool isModified)
{
    m_fileName = fileName;
    m_isNew = isNew;
    m_isModified = isModified;
    emit statusChanged(this);
}

#include <QFile>
#include <QSaveFile>
#include <QBoxLayout>
#include <QTableView>
#include <QHeaderView>
#include <QJsonDocument>
#include "SchemeModel.h"
#include "SchemeWidget.h"
#include "SchemeDelegate.h"

SchemeWidget::SchemeWidget(const QString &fileName, QWidget *parent)
    : QWidget(parent),
      m_model(new SchemeModel(this)),
      m_view(new QTableView),
      m_fileName(fileName),
      m_isNew(true),
      m_isModified(false)
{
    connect(m_model, &SchemeModel::dataChanged, this, &SchemeWidget::changeStatus);
    connect(m_model, &SchemeModel::rowsInserted, this, &SchemeWidget::changeStatus);
    connect(m_model, &SchemeModel::rowsInserted, this, &SchemeWidget::selectInsertedRows);
    connect(m_model, &SchemeModel::rowsRemoved, this, &SchemeWidget::changeStatus);
    connect(m_model, &SchemeModel::rowsMoved, this, &SchemeWidget::changeStatus);

    m_view->setItemDelegate(new SchemeDelegate(this));
    m_view->setSelectionBehavior(QTableView::SelectRows);
    m_view->setSelectionMode(QTableView::ContiguousSelection);

    m_view->horizontalHeader()->setHighlightSections(false);
    m_view->setAlternatingRowColors(true);
    m_view->setModel(m_model);

    QBoxLayout * const layout = new QVBoxLayout(this);
    layout->addWidget(m_view);
}

QString SchemeWidget::fileName() const
{
    return m_fileName;
}

bool SchemeWidget::isNew() const
{
    return m_isNew;
}

bool SchemeWidget::isModified() const
{
    return m_isModified;
}

bool SchemeWidget::loadFromFile(const QString &fileName)
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

bool SchemeWidget::saveToFile(const QString &fileName)
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

void SchemeWidget::insertItem()
{
    m_model->insertRow(m_model->rowCount());
}

void SchemeWidget::removeItems()
{
    QModelIndexList indexes = m_view->selectionModel()->selectedRows();
    if (!indexes.isEmpty())
    {
        qSort(indexes);
        m_model->removeRows(indexes.first().row(), indexes.count());
    }
}

void SchemeWidget::moveItemsUp()
{
    QModelIndexList indexes = m_view->selectionModel()->selectedRows();
    if (!indexes.isEmpty())
    {
        qSort(indexes);
        m_model->moveRows(QModelIndex(), indexes.first().row(), indexes.count(), QModelIndex(), indexes.first().row() - 1);
    }
}

void SchemeWidget::moveItemsDown()
{
    QModelIndexList indexes = m_view->selectionModel()->selectedRows();
    if (!indexes.isEmpty())
    {
        qSort(indexes);
        m_model->moveRows(QModelIndex(), indexes.first().row(), indexes.count(), QModelIndex(), indexes.last().row() + 2);
    }
}

void SchemeWidget::changeStatus()
{
    setStatus(m_fileName, m_isNew, true);
}

void SchemeWidget::selectInsertedRows(const QModelIndex &index, int first, int last)
{
    Q_UNUSED(index)
    Q_UNUSED(first)

    m_view->selectRow(last);
}

void SchemeWidget::setStatus(const QString &fileName, bool isNew, bool isModified)
{
    m_fileName = fileName;
    m_isNew = isNew;
    m_isModified = isModified;
    emit statusChanged(this);
}

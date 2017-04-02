#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include "Delegate.h"
#include "SchemeModel.h"

SchemeModel::SchemeModel(QObject *parent) :
    QAbstractTableModel(parent),
    m_columnCount(0)
{
}

int SchemeModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_items.count();
}

int SchemeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_columnCount;
}

QVariant SchemeModel::data(const QModelIndex &index, int role) const
{
    const SchemeItem &item = m_items.at(index.row());

    if (role == Qt::DisplayRole)
        return item.value(index.column());

    if (role == Qt::EditRole)
        return item.value(index.column());

    if (role == Qt::UserRole)
        return item.delegate(index.column());

    return QVariant();
}

bool SchemeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    SchemeItem &item = m_items[index.row()];

    if (role == Qt::EditRole)
    {
        if (item.setValue(index.column(), value))
        {
            updateColumnCount(index.parent());
            emit dataChanged(index, index);
            return true;
        }
    }

    return false;
}

QVariant SchemeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QAbstractTableModel::headerData(section, orientation, role);
}

Qt::ItemFlags SchemeModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

bool SchemeModel::insertRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent)

    beginInsertRows(parent, row, row + count - 1);
    while (count--)
        m_items.insert(row, SchemeItem());

    updateColumnCount(parent);
    endInsertRows();

    return true;
}

bool SchemeModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent)

    beginRemoveRows(parent, row, row + count - 1);
    while (count--)
        m_items.removeAt(row);

    updateColumnCount(parent);
    endRemoveRows();

    return true;
}

bool SchemeModel::moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationChild)
{
    Q_UNUSED(sourceParent)
    Q_UNUSED(destinationParent)

    if (destinationChild < 0 || destinationChild > rowCount() || sourceRow + 1 == destinationChild)
        return false;

    beginMoveRows(sourceParent, sourceRow, sourceRow + count - 1, destinationParent, destinationChild);
    if (destinationChild < sourceRow)
    {
        while (count--)
            m_items.move(sourceRow++, destinationChild++);
    }
    else
    {
        sourceRow += count;
        while (count--)
            m_items.move(--sourceRow, --destinationChild);
    }
    endMoveRows();

    return true;
}

void SchemeModel::readFromJson(const QJsonDocument &document)
{
    beginResetModel();

    m_items.clear();
    foreach (const QJsonValue &value, document.array())
    {
        SchemeItem item;
        item.readFromJson(value.toObject());
        m_items.append(item);
    }

    m_columnCount = actualColumnCount();

    endResetModel();
}

QJsonDocument SchemeModel::writeToJson() const
{
    QJsonArray array;
    foreach (const SchemeItem &item, m_items)
        array.append(item.writeToJson());

    return QJsonDocument(array);
}

void SchemeModel::updateColumnCount(const QModelIndex &index)
{
    const int count = actualColumnCount();

    if (count > m_columnCount)
    {
        beginInsertColumns(index, m_columnCount, count - 1);
        m_columnCount = count;
        endInsertColumns();
    }

    if (count < m_columnCount)
    {
        beginRemoveColumns(index, count, m_columnCount - 1);
        m_columnCount = count;
        endRemoveColumns();
    }
}

int SchemeModel::actualColumnCount() const
{
    int count = 0;
    foreach (const SchemeItem &item, m_items)
        count = qMax(count, item.count());

    return count;
}

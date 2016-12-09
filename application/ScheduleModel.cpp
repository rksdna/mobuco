#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include "Delegate.h"
#include "ScheduleModel.h"

ScheduleModel::ScheduleModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_entries.append(ScheduleEntry(0));
    m_entries.append(ScheduleEntry(1));
    m_entries.append(ScheduleEntry(2));
    m_entries.append(ScheduleEntry(3));
}

int ScheduleModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_entries.count();
}

int ScheduleModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return count();
}

QVariant ScheduleModel::data(const QModelIndex &index, int role) const
{
    const ScheduleEntry &entry = m_entries.at(index.row());

    if (role == Qt::DisplayRole)
        return entry.value(index.column());

    if (role == Qt::EditRole)
        return entry.value(index.column());

    if (role == Qt::UserRole)
        return entry.delegate(index.column());

    return QVariant();
}

bool ScheduleModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    ScheduleEntry &entry = m_entries[index.row()];

    if (role == Qt::EditRole)
    {
        if (entry.setValue(index.column(), value))
        {
            emit dataChanged(index, index);
            return true;
        }
    }

    return false;
}

QVariant ScheduleModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QAbstractTableModel::headerData(section, orientation, role);
}

Qt::ItemFlags ScheduleModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

bool ScheduleModel::insertRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent)

    beginInsertRows(parent, row, row + count - 1);
    while (count--)
        m_entries.insert(row, ScheduleEntry());
    endInsertRows();
    return true;
}

bool ScheduleModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent)

    beginRemoveRows(parent, row, row + count - 1);
    while (count--)
        m_entries.removeAt(row);
    endRemoveRows();
    return true;
}

bool ScheduleModel::moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationChild)
{
    Q_UNUSED(sourceParent)
    Q_UNUSED(destinationParent)

    if (destinationChild < 0 || destinationChild > rowCount() || sourceRow + 1 == destinationChild)
        return false;

    beginMoveRows(sourceParent, sourceRow, sourceRow + count - 1, destinationParent, destinationChild);
    if (destinationChild < sourceRow)
    {
        while (count--)
            m_entries.move(sourceRow++, destinationChild++);
    }
    else
    {
        sourceRow += count;
        while (count--)
            m_entries.move(--sourceRow, --destinationChild);
    }
    endMoveRows();

    return true;
}

void ScheduleModel::readFromJson(const QJsonDocument &document)
{
    beginResetModel();

    m_entries.clear();
    foreach (const QJsonValue &value, document.array())
    {
        ScheduleEntry entry;
        entry.readFromJson(value.toObject());
        m_entries.append(entry);
    }

    endResetModel();
}

QJsonDocument ScheduleModel::writeToJson() const
{
    QJsonArray array;
    foreach (const ScheduleEntry &entry, m_entries)
        array.append(entry.writeToJson());

    return QJsonDocument(array);
}

int ScheduleModel::count() const
{
    int count = 0;
    foreach (const ScheduleEntry &entry, m_entries)
        count = qMax(count, entry.count());

    return count;
}

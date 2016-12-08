#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include "Delegate.h"
#include "ScheduleModel.h"

ScheduleModel::ScheduleModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_entries.append(ScheduleEntry(2));
    m_entries.append(ScheduleEntry(3));
    m_entries.append(ScheduleEntry(4));
}

int ScheduleModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_entries.count();
}

int ScheduleModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : count();
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
    const ScheduleEntry &entry = m_entries.at(index.row());
    return index.column() < entry.count() ? Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable : Qt::NoItemFlags;
}

int ScheduleModel::count() const
{
    int count = 0;
    foreach (const ScheduleEntry &entry, m_entries)
        count = qMax(count, entry.count());

    return count;
}

bool ScheduleModel::insertRows(int row, int count, const QModelIndex &parent)
{
    return false;
}

bool ScheduleModel::removeRows(int row, int count, const QModelIndex &parent)
{
    return false;
}

bool ScheduleModel::moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationChild)
{
    return false;
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

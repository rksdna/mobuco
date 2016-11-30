#include <QIcon>
#include "ScheduleWidget.h"
#include "PickScheduleModel.h"

PickScheduleModel::PickScheduleModel(const QList<ScheduleWidget *> &items, QObject *parent)
    : QAbstractListModel(parent)
{
    foreach (ScheduleWidget *item, items)
        m_items.insert(item, true);
}

int PickScheduleModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_items.count();
}

QVariant PickScheduleModel::data(const QModelIndex &index, int role) const
{
    ScheduleWidget * const key = m_items.keys().at(index.row());

    switch (role)
    {
    case Qt::DisplayRole:
        return key->fileName();

    case Qt::DecorationRole:
        return QIcon::fromTheme("text-x-generic");

    case Qt::CheckStateRole:
        return m_items.value(key) ? Qt::Checked : Qt::Unchecked;

    default:
        break;
    }

    return QVariant();
}

bool PickScheduleModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    ScheduleWidget * const key = m_items.keys().at(index.row());

    if (role == Qt::CheckStateRole)
    {
        m_items[key] = value.toBool();
        emit dataChanged(index, index);
        return true;
    }

    return false;
}

Qt::ItemFlags PickScheduleModel::flags(const QModelIndex &index) const
{
    return index.isValid() ?
                Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable :
                Qt::NoItemFlags;
}

QList<ScheduleWidget *> PickScheduleModel::items() const
{
    return m_items.keys();
}

QList<ScheduleWidget *> PickScheduleModel::selectedItems() const
{
    return m_items.keys(true);
}

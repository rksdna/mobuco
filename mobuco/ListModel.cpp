#include "ListModel.h"
#include "ScheduleWidget.h"

ListModel::ListModel(const QList<ScheduleWidget *> &widgets, QObject *parent)
    : QAbstractTableModel(parent),
      m_widgets(widgets)
{

}

int ListModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_widgets.count();
}

int ListModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : ColumnsCount;
}

QVariant ListModel::data(const QModelIndex &index, int role) const
{
    const ScheduleWidget *widget = m_widgets.at(index.row());
    int column = index.column();

    switch (role)
    {
    case Qt::DisplayRole:
        if (column == FileNameColumn)
            return widget->fileName();
        break;

    default:
        break;
    }

    return QVariant();
}

QVariant ListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QAbstractTableModel::headerData(section, orientation, role);
}

Qt::ItemFlags ListModel::flags(const QModelIndex &index) const
{
    return index.isValid() ? Qt::ItemIsEnabled | Qt::ItemIsSelectable : Qt::NoItemFlags;
}

ScheduleWidget *ListModel::widget(const QModelIndex &index) const
{
    return m_widgets.at(index.row());

}

#ifndef PICKSCHEDULEMODEL_H
#define PICKSCHEDULEMODEL_H

#include <QMap>
#include <QAbstractTableModel>

class ScheduleWidget;

class PickScheduleModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit PickScheduleModel(const QList<ScheduleWidget *> &items, QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;

    QList<ScheduleWidget *> items() const;
    QList<ScheduleWidget *> selectedItems() const;

private:
    QMap<ScheduleWidget *, bool> m_items;
};

#endif // PICKSCHEDULEMODEL_H

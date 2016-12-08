#ifndef SCHEDULEMODEL_H
#define SCHEDULEMODEL_H

#include <QAbstractTableModel>
#include "ScheduleEntry.h"

class ScheduleModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ScheduleModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool insertRows(int row, int count, const QModelIndex &parent);
    bool removeRows(int row, int count, const QModelIndex &parent);
    bool moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationChild);

    void readFromJson(const QJsonDocument &document);
    QJsonDocument writeToJson() const;

private:
    int count() const;

private:
    QList<ScheduleEntry> m_entries;
};

#endif // SCHEDULEMODEL_H
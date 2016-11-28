#ifndef LISTMODEL_H
#define LISTMODEL_H

#include <QAbstractTableModel>

class ScheduleWidget;

class ListModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ListModel(const QList<ScheduleWidget *> &widgets, QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    ScheduleWidget *widget(const QModelIndex &index) const;

private:
    enum
    {
        FileNameColumn,
        ColumnsCount
    };

private:
    QList<ScheduleWidget *> m_widgets;

};

#endif // LISTMODEL_H

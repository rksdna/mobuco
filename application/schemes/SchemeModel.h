#ifndef SCHEMEMODEL_H
#define SCHEMEMODEL_H

#include <QAbstractTableModel>
#include "SchemeItem.h"

class SchemeModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit SchemeModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
    bool moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationChild);

    void readFromJson(const QJsonDocument &document);
    QJsonDocument writeToJson() const;

private:
    int count() const;

private:
    QList<SchemeItem> m_entries;
};

#endif // SCHEMEMODEL_H

#ifndef PICKSCHEMEMODEL_H
#define PICKSCHEMEMODEL_H

#include <QMap>
#include <QAbstractTableModel>

class SchemeWidget;

class PickSchemeModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit PickSchemeModel(const QList<SchemeWidget *> &schemes, QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;

    QList<SchemeWidget *> schemes() const;
    QList<SchemeWidget *> selectedSchemes() const;

private:
    QMap<SchemeWidget *, bool> m_schemes;
};

#endif // PICKSCHEMEMODEL_H

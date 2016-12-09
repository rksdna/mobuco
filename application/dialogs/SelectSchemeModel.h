#ifndef SELECTSCHEMEMODEL_H
#define SELECTSCHEMEMODEL_H

#include <QMap>
#include <QAbstractTableModel>

class SchemeWidget;

class SelectSchemeModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit SelectSchemeModel(const QList<SchemeWidget *> &schemes, QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;

    QList<SchemeWidget *> schemes() const;
    QList<SchemeWidget *> selectedSchemes() const;

private:
    QMap<SchemeWidget *, bool> m_schemes;
};

#endif // SELECTSCHEMEMODEL_H

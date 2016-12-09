#include <QIcon>
#include "SchemeWidget.h"
#include "SelectSchemeModel.h"

SelectSchemeModel::SelectSchemeModel(const QList<SchemeWidget *> &schemes, QObject *parent)
    : QAbstractListModel(parent)
{
    foreach (SchemeWidget *scheme, schemes)
        m_schemes.insert(scheme, true);
}

int SelectSchemeModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_schemes.count();
}

QVariant SelectSchemeModel::data(const QModelIndex &index, int role) const
{
    SchemeWidget * const scheme = m_schemes.keys().at(index.row());

    switch (role)
    {
    case Qt::DisplayRole:
        return scheme->fileName();

    case Qt::DecorationRole:
        return QIcon::fromTheme("text-x-generic");

    case Qt::CheckStateRole:
        return m_schemes.value(scheme) ? Qt::Checked : Qt::Unchecked;

    default:
        break;
    }

    return QVariant();
}

bool SelectSchemeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    SchemeWidget * const scheme = m_schemes.keys().at(index.row());

    if (role != Qt::CheckStateRole)
        return false;

    m_schemes[scheme] = value.toBool();
    emit dataChanged(index, index);
    return true;
}

Qt::ItemFlags SelectSchemeModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
}

QList<SchemeWidget *> SelectSchemeModel::schemes() const
{
    return m_schemes.keys();
}

QList<SchemeWidget *> SelectSchemeModel::selectedSchemes() const
{
    return m_schemes.keys(true);
}

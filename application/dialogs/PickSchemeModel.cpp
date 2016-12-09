#include <QIcon>
#include "SchemeWidget.h"
#include "PickSchemeModel.h"

PickSchemeModel::PickSchemeModel(const QList<SchemeWidget *> &schemes, QObject *parent)
    : QAbstractListModel(parent)
{
    foreach (SchemeWidget *scheme, schemes)
        m_schemes.insert(scheme, true);
}

int PickSchemeModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_schemes.count();
}

QVariant PickSchemeModel::data(const QModelIndex &index, int role) const
{
    SchemeWidget * const key = m_schemes.keys().at(index.row());

    switch (role)
    {
    case Qt::DisplayRole:
        return key->fileName();

    case Qt::DecorationRole:
        return QIcon::fromTheme("text-x-generic");

    case Qt::CheckStateRole:
        return m_schemes.value(key) ? Qt::Checked : Qt::Unchecked;

    default:
        break;
    }

    return QVariant();
}

bool PickSchemeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    SchemeWidget * const key = m_schemes.keys().at(index.row());

    if (role == Qt::CheckStateRole)
    {
        m_schemes[key] = value.toBool();
        emit dataChanged(index, index);
        return true;
    }

    return false;
}

Qt::ItemFlags PickSchemeModel::flags(const QModelIndex &index) const
{
    return index.isValid() ? Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable : Qt::NoItemFlags;
}

QList<SchemeWidget *> PickSchemeModel::schemes() const
{
    return m_schemes.keys();
}

QList<SchemeWidget *> PickSchemeModel::selectedSchemes() const
{
    return m_schemes.keys(true);
}

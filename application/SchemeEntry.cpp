#include <QJsonArray>
#include <QJsonObject>
#include "SchemeEntry.h"
#include "EnumerationDelegate.h"

SchemeEntry::SchemeEntry(int size)
    : m_data(size)
{
}

int SchemeEntry::count() const
{
    return m_data.count();
}

QVariant SchemeEntry::value(int column) const
{
    return m_data.value(column, -200);
}

bool SchemeEntry::setValue(int column, const QVariant &value)
{
    m_data[column] = value.toInt();
    return true;
}

QVariant SchemeEntry::delegate(int column) const
{
    static DelegateSharedPointer da(new EnumerationDelegate("A;B;C"));
    static DelegateSharedPointer db(new EnumerationDelegate("q;w;e"));

    if (column == 0)
        return QVariant::fromValue(DelegateSharedPointer(new EnumerationDelegate("r;t;y")));

    if (column % 2 == 0)
        return QVariant::fromValue(da);

    return QVariant::fromValue(db);
}

void SchemeEntry::readFromJson(const QJsonObject &object)
{
    QJsonArray data = object["data"].toArray();

    m_data.resize(data.count());
    for (int i = 0; i < m_data.count(); i++)
        m_data[i] = data.at(i).toInt();
}

QJsonObject SchemeEntry::writeToJson() const
{
    QJsonArray data;
    for (int i = 0; i < m_data.count(); i++)
        data.append(m_data.at(i));

    QJsonObject object;
    object["data"] = data;
    return object;
}

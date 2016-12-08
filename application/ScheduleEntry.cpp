#include "Delegate.h"
#include "ScheduleEntry.h"

ScheduleEntry::ScheduleEntry(int size)
    : m_data(size)
{
}

int ScheduleEntry::count() const
{
    return m_data.count();
}

QVariant ScheduleEntry::value(int column) const
{
    return m_data.value(column, -200);
}

bool ScheduleEntry::setValue(int column, const QVariant &value)
{
    m_data[column] = value.toInt();
    return true;
}

Delegate *ScheduleEntry::delegate(int column) const
{
    static ComboDelegate da("A;B;C");
    static ComboDelegate db("q;w;e");

    if (column % 2 == 0)
        return &da;

    return &db;
}

#include <QJsonArray>
#include <QJsonObject>
#include "SchemeItem.h"
#include "FunctionType.h"
#include "DefaultDelegate.h"
#include "FunctionDelegate.h"

SchemeItem::SchemeItem()
    : m_function(create(0x00))
{
}

int SchemeItem::count() const
{
    return FixedColumnCount;
}

QVariant SchemeItem::data(int column) const
{
    if (column == CodeColumn)
        return m_function->type().code();

    return QVariant();
}

bool SchemeItem::setData(int column, const QVariant &value)
{
    if (column == CodeColumn)
    {
        m_function = create(value.toInt());
        return true;
    }

    return false;
}

Delegate::Pointer SchemeItem::delegate(int column) const
{
    if (column == CodeColumn)
        return Delegate::shared<FunctionDelegate>();

    return Delegate::shared<DefaultDelegate>();
}

void SchemeItem::readFromJson(const QJsonObject &object)
{
    m_function = create(object["function"].toInt());
}

QJsonObject SchemeItem::writeToJson() const
{
    QJsonObject object;
    object["function"] = m_function->type().code();

    return object;
}

Function::Pointer SchemeItem::create(int code)
{
    const FunctionType::Pointer type = FunctionType::types().value(code);
#warning "Fix me"
    return type ? type->create() : Function::Pointer();
}

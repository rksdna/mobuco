#include "FunctionType.h"

FunctionType::FunctionType(int code, const QString &title)
    : m_code(code),
      m_title(title)
{
    FunctionFactory::instance()->append(this);
}

int FunctionType::code() const
{
    return m_code;
}

QString FunctionType::title() const
{
    return m_title;
}

FunctionFactory *FunctionFactory::instance()
{
    static FunctionFactory factory;
    return &factory;
}

FunctionFactory::FunctionFactory()
{
}

QList<int> FunctionFactory::codes() const
{
    return m_types.keys();
}

const FunctionType *FunctionFactory::type(int code) const
{
    return m_types.value(code);
}

void FunctionFactory::append(const FunctionType *type)
{
    m_types.insert(type->code(), type);
}

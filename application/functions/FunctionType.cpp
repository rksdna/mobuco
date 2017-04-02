#include "FunctionType.h"

FunctionType::FunctionType(int code, const QString &title)
    : m_code(code),
      m_title(title)
{
    types().insert(code, this);
}

int FunctionType::code() const
{
    return m_code;
}

QString FunctionType::title() const
{
    return m_title;
}

FunctionType::Hash &FunctionType::types()
{
    static Hash types;
    return types;
}

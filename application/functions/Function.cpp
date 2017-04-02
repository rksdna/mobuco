#include "Function.h"

Function::Function(const FunctionType *type)
    : m_type(type)
{
}

const FunctionType *Function::type() const
{
    return m_type;
}

Function::~Function()
{
}

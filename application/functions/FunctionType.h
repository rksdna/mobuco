#ifndef FUNCTIONTYPE_H
#define FUNCTIONTYPE_H

#include <QHash>
#include "Function.h"

class FunctionType
{
public:
    typedef const FunctionType *Pointer;
    typedef QHash<int, Pointer> Hash;

public:
    static Hash &types();

public:
    FunctionType(int code, const QString &title);
    int code() const;
    QString title() const;

    virtual Function::Pointer create() const = 0;

private:
    const int m_code;
    const QString m_title;
};

template <typename CustomFunction>
class CustomFunctionType : public FunctionType
{
public:
    explicit CustomFunctionType(int code, const QString &title)
        : FunctionType(code, title)
    {
    }

    Function::Pointer create() const
    {
        return Function::Pointer(new CustomFunction);
    }
};

#endif // FUNCTIONTYPE_H

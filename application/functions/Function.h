#ifndef FUNCTION_H
#define FUNCTION_H

#include <QApplication>
#include <QSharedPointer>

class FunctionType;

class Function
{
    Q_DECLARE_TR_FUNCTIONS(Function)
public:
    typedef QSharedPointer<Function> Pointer;

public:
    explicit Function(const FunctionType &type);
    const FunctionType &type() const;
    virtual ~Function();

private:
    const FunctionType &m_type;
};

#endif // FUNCTION_H

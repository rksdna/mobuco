#ifndef FUNCTIONTYPE_H
#define FUNCTIONTYPE_H

#include <QHash>

class Function;

class FunctionType
{
public:
    FunctionType(int code, const QString &title);
    int code() const;
    QString title() const;

    virtual Function *create() const = 0;

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

    Function *create() const
    {
        return new CustomFunction;
    }
};

class FunctionFactory
{
public:
    static FunctionFactory *instance();

public:
    QList<int> codes() const;
    const FunctionType *type(int code) const;
    void append(const FunctionType *type);

private:
    FunctionFactory();
    Q_DISABLE_COPY(FunctionFactory)

private:
    QHash<int, const FunctionType *> m_types;
};

#endif // FUNCTIONTYPE_H

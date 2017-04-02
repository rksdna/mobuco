#ifndef SCHEMEITEM_H
#define SCHEMEITEM_H

#include "Function.h"
#include "Delegate.h"

class Delegate;
class Function;
class QJsonObject;

class SchemeItem
{
public:
    SchemeItem();
    int count() const;
    QVariant data(int column) const;
    bool setData(int column, const QVariant &data);
    Delegate::Pointer delegate(int column) const;

    void readFromJson(const QJsonObject &object);
    QJsonObject writeToJson() const;

private:
    enum FixedColumn
    {
        StatusColumn,
        CodeColumn,
        FixedColumnCount
    };
private:
    static Function::Pointer create(int code);

private:
    Function::Pointer m_function;
};

#endif // SCHEMEITEM_H

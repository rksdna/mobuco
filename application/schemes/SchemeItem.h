#ifndef SCHEMEITEM_H
#define SCHEMEITEM_H

#include <QVector>
#include <QVariant>

class Delegate;
class QJsonObject;

class SchemeItem
{
public:
    SchemeItem(int size = 2);
    int count() const;
    QVariant value(int column) const;
    bool setValue(int column, const QVariant &value);
    QVariant delegate(int column) const;

    void readFromJson(const QJsonObject &object);
    QJsonObject writeToJson() const;

private:
    QVector<int> m_data;
};

#endif // SCHEMEITEM_H

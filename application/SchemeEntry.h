#ifndef SCHEMEENTRY_H
#define SCHEMEENTRY_H

#include <QVector>
#include <QVariant>

class Delegate;
class QJsonObject;

class SchemeEntry
{
public:
    SchemeEntry(int size = 2);
    int count() const;
    QVariant value(int column) const;
    bool setValue(int column, const QVariant &value);
    QVariant delegate(int column) const;

    void readFromJson(const QJsonObject &object);
    QJsonObject writeToJson() const;

private:
    QVector<int> m_data;
};

#endif // SCHEMEENTRY_H

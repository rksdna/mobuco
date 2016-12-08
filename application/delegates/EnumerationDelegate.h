#ifndef ENUMERATIONDELEGATE_H
#define ENUMERATIONDELEGATE_H

#include <QString>
#include "Delegate.h"

class EnumerationDelegate : public Delegate
{
public:
    EnumerationDelegate(const QString &items);
    QWidget *createWidget(QWidget *parent) const;
    void destroyEditor(QWidget *editor) const;
    void setEditorData(QWidget *editor, const QVariant &data) const;
    QVariant editorData(QWidget *editor) const;

private:
    const QString m_items;
};

#endif // ENUMERATIONDELEGATE_H

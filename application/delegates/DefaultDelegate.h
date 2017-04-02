#ifndef DEFAULTDELEGATE_H
#define DEFAULTDELEGATE_H

#include "Delegate.h"

class DefaultDelegate : public Delegate
{
public:
    QVariant display(const QVariant &data) const;
    QVariant decoration(const QVariant &data) const;
    bool isEditable() const;

    QWidget *createEditor(QWidget *parent) const;
    void destroyEditor(QWidget *editor) const;
    void setEditorData(QWidget *editor, const QVariant &data) const;
    QVariant editorData(QWidget *editor) const;
};

#endif // DEFAULTDELEGATE_H

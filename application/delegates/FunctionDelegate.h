#ifndef FUNCTIONDELEGATE_H
#define FUNCTIONDELEGATE_H

#include "Delegate.h"

class FunctionDelegate : public Delegate
{
public:
    QVariant display(const QVariant &data) const;
    QVariant decoration(const QVariant &data) const;
    bool isEditable() const;

    QWidget *createEditor(QWidget *parent) const;
    void destroyEditor(QWidget *editor) const;
    void setEditorData(QWidget *editor, const QVariant &data) const;
    QVariant editorData(QWidget *editor) const;

private:
    static QString toString(int code);
};

#endif // FUNCTIONDELEGATE_H

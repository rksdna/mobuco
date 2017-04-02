#include "DefaultDelegate.h"

QVariant DefaultDelegate::display(const QVariant &data) const
{
    Q_UNUSED(data)

    return QVariant();
}

QVariant DefaultDelegate::decoration(const QVariant &data) const
{
    Q_UNUSED(data)

    return QVariant();
}

bool DefaultDelegate::isEditable() const
{
    return false;
}

QWidget *DefaultDelegate::createEditor(QWidget *parent) const
{
    Q_UNUSED(parent)
    return 0;
}

void DefaultDelegate::destroyEditor(QWidget *editor) const
{
    Q_UNUSED(editor)
}

void DefaultDelegate::setEditorData(QWidget *editor, const QVariant &data) const
{
    Q_UNUSED(editor)
    Q_UNUSED(data)
}

QVariant DefaultDelegate::editorData(QWidget *editor) const
{
    Q_UNUSED(editor)

    return QVariant();
}

#include "Delegate.h"
#include "SchemeDelegate.h"

SchemeDelegate::SchemeDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

QWidget *SchemeDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Delegate::Pointer const delegate = index.data(Qt::UserRole).value<Delegate::Pointer>();
    if (delegate)
        return delegate->createEditor(parent);

    return QItemDelegate::createEditor(parent, option, index);
}

void SchemeDelegate::destroyEditor(QWidget *editor, const QModelIndex &index) const
{
    Delegate::Pointer const delegate = index.data(Qt::UserRole).value<Delegate::Pointer>();
    if (delegate)
        return delegate->destroyEditor(editor);

    return QItemDelegate::destroyEditor(editor, index);
}

void SchemeDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    Delegate::Pointer const delegate = index.data(Qt::UserRole).value<Delegate::Pointer>();
    if (delegate)
        delegate->setEditorData(editor, index.data(Qt::EditRole));
    else
        QItemDelegate::setEditorData(editor, index);
}

void SchemeDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    Delegate::Pointer const delegate = index.data(Qt::UserRole).value<Delegate::Pointer>();
    if (delegate)
        model->setData(index, delegate->editorData(editor), Qt::EditRole);
    else
        QItemDelegate::setModelData(editor, model, index);
}

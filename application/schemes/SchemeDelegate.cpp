#include "Delegate.h"
#include "SchemeDelegate.h"

SchemeDelegate::SchemeDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

QWidget *SchemeDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    DelegateSharedPointer const delegate = index.data(Qt::UserRole).value<DelegateSharedPointer>();
    if (delegate)
        return delegate->createWidget(parent);

    return QItemDelegate::createEditor(parent, option, index);
}

void SchemeDelegate::destroyEditor(QWidget *editor, const QModelIndex &index) const
{
    DelegateSharedPointer const delegate = index.data(Qt::UserRole).value<DelegateSharedPointer>();
    if (delegate)
        return delegate->destroyEditor(editor);

    return QItemDelegate::destroyEditor(editor, index);
}

void SchemeDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    DelegateSharedPointer const delegate = index.data(Qt::UserRole).value<DelegateSharedPointer>();
    if (delegate)
        delegate->setEditorData(editor, index.data(Qt::EditRole));
    else
        QItemDelegate::setEditorData(editor, index);
}

void SchemeDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    DelegateSharedPointer const delegate = index.data(Qt::UserRole).value<DelegateSharedPointer>();
    if (delegate)
        model->setData(index, delegate->editorData(editor), Qt::EditRole);
    else
        QItemDelegate::setModelData(editor, model, index);
}

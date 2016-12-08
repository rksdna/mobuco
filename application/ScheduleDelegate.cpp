#include "Delegate.h"
#include "ScheduleDelegate.h"

ScheduleDelegate::ScheduleDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

QWidget *ScheduleDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Delegate * const delegate = index.data(Qt::UserRole).value<Delegate *>();
    if (delegate)
        return delegate->createWidget(parent);

    return QItemDelegate::createEditor(parent, option, index);
}

void ScheduleDelegate::destroyEditor(QWidget *editor, const QModelIndex &index) const
{
    Delegate * const delegate = index.data(Qt::UserRole).value<Delegate *>();
    if (delegate)
        return delegate->destroyEditor(editor);

    return QItemDelegate::destroyEditor(editor, index);
}

void ScheduleDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    Delegate * const delegate = index.data(Qt::UserRole).value<Delegate *>();
    if (delegate)
        delegate->setEditorData(editor, index.data(Qt::EditRole));
    else
        QItemDelegate::setEditorData(editor, index);
}

void ScheduleDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    Delegate * const delegate = index.data(Qt::UserRole).value<Delegate *>();
    if (delegate)
        model->setData(index, delegate->editorData(editor), Qt::EditRole);
    else
        QItemDelegate::setModelData(editor, model, index);
}

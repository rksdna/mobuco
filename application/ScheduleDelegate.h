#ifndef SCHEDULEDELEGATE_H
#define SCHEDULEDELEGATE_H

#include <QItemDelegate>

class ScheduleDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit ScheduleDelegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void destroyEditor(QWidget *editor, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
};

#endif // SCHEDULEDELEGATE_H

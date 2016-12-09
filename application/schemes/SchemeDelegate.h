#ifndef SCHEMEDELEGATE_H
#define SCHEMEDELEGATE_H

#include <QItemDelegate>

class SchemeDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit SchemeDelegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void destroyEditor(QWidget *editor, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
};

#endif // SCHEMEDELEGATE_H

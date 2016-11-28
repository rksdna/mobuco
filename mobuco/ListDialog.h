#ifndef LISTDIALOG_H
#define LISTDIALOG_H

#include <QDialog>

class QTreeView;
class ListModel;
class ScheduleWidget;

class ListDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ListDialog(const QList<ScheduleWidget *> &widgets, QWidget *parent = 0);

signals:
    void selected(const QList<ScheduleWidget *> widgets);

private slots:
    void save();
    void discard();

private:
    ListModel * const m_model;
    QTreeView * const m_view;
};

#endif // LISTDIALOG_H

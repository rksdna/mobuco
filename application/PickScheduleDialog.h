#ifndef PICKCHEDULEDIALOG_H
#define PICKSCHEDULEDIALOG_H

#include <QDialog>

class ScheduleWidget;
class PickScheduleModel;

class PickScheduleDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PickScheduleDialog(const QString &text, const QList<ScheduleWidget *> &items, QWidget *parent = 0);

signals:
    void itemsSelected(const QList<ScheduleWidget *> &items);

protected:
    void hideEvent(QHideEvent *event);

private slots:
    void yes();
    void no();
    void cancel();

private:
    PickScheduleModel * const m_model;
};

#endif // PICKSCHEDULEDIALOG_H

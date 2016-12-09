#ifndef SCHEDULEWIDGET_H
#define SCHEDULEWIDGET_H

#include <QWidget>
#include <QPersistentModelIndex>

class QTableView;
class ScheduleModel;

class ScheduleWidget : public QWidget
{
    Q_OBJECT
public:
    enum Move
    {
        MoveToTop,
        MoveUp,
        MoveDown,
        MoveToBottom
    };

public:
    explicit ScheduleWidget(const QString &fileName, QWidget *parent = 0);
    QString fileName() const;
    bool isNew() const;
    bool isModified() const;
    bool loadFromFile(const QString &fileName);
    bool saveToFile(const QString &fileName);
    void insertEntry();
    void removeEntries();
    void moveEntries(Move move);

signals:
    void statusChanged(ScheduleWidget *item);

private slots:
    void changeStatus();
    void selectInsertedRows(const QModelIndex &index, int first, int last);

private:
    void setStatus(const QString &fileName, bool isNew, bool isModified);

private:
    ScheduleModel * const m_model;
    QTableView * const m_view;
    QString m_fileName;
    bool m_isNew;
    bool m_isModified;
};

#endif // SCHEDULEWIDGET_H

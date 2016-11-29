#ifndef SCHEDULEWIDGET_H
#define SCHEDULEWIDGET_H

#include <QWidget>

class ScheduleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ScheduleWidget(const QString &fileName, QWidget *parent = 0);
    QString fileName() const;
    bool isNew() const;
    bool isModified() const;
    bool loadFromFile(const QString &fileName);
    bool saveToFile(const QString &fileName);

signals:
    void statusChanged(ScheduleWidget *item);

private slots:
    void touch();

private:
    void setStatus(const QString &fileName, bool isNew, bool isModified);

private:
    QString m_fileName;
    bool m_isNew;
    bool m_isModified;
};

#endif // SCHEDULEWIDGET_H

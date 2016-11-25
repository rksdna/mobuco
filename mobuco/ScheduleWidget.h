#ifndef SCHEDULEWIDGET_H
#define SCHEDULEWIDGET_H

#include <QWidget>

class ScheduleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ScheduleWidget(QWidget *parent = 0);
    QString fileName() const;
    bool isModified() const;
    void createNew();
    bool loadFromFile(const QString &fileName);
    bool saveToFile(const QString &fileName);

signals:
    void modified(ScheduleWidget *widget);

private slots:
    void touch();

private:
    void setFileState(const QString &fileName, bool modified);

private:
    QString _fileName;
    bool _modified;
};

#endif // SCHEDULEWIDGET_H

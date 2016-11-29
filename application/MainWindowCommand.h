#ifndef MAINWINDOWCOMMAND_H
#define MAINWINDOWCOMMAND_H

#include <QObject>
#include <QStringList>

class MainWindow;
class ScheduleWidget;

class Command : public QObject
{
    Q_OBJECT
public:
    explicit Command(MainWindow *parent);
    ~Command();

signals:
    void completed();
    void aborted();

protected:
    MainWindow *window() const;
    void showErrorMessage(const QString &text);

private:
    MainWindow * const m_window;
};

class NewCommand : public Command
{
    Q_OBJECT
public:
    explicit NewCommand(MainWindow *parent);
    void execute();
};

class OpenCommand : public Command
{
    Q_OBJECT
public:
    explicit OpenCommand(MainWindow *parent);
    void execute();

private slots:
    void process(const QStringList &fileNames);
};

class SaveCommand : public Command
{
    Q_OBJECT
public:
    SaveCommand(const QList<ScheduleWidget *> &items, MainWindow *parent);
    void setAskFileName(bool askFileName);
    void execute();

signals:
    void itemSaved(ScheduleWidget *item);

private slots:
    void process(const QString &fileName);

private:
    bool m_askFileName;
    QList<ScheduleWidget *> m_items;
    QStringList m_errors;
};

class CloseCommand : public Command
{
    Q_OBJECT
public:
    CloseCommand(const QList<ScheduleWidget *> &items, MainWindow *parent);
    void execute();

private slots:
    void process(const QList<ScheduleWidget *> &items);
    void closeItem(ScheduleWidget *item);

private:
    QList<ScheduleWidget *> m_items;
};

#endif // MAINWINDOWCOMMAND_H

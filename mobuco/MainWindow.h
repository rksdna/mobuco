#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QTabWidget;
class ScheduleWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);

protected:
    void hideEvent(QHideEvent *event);
    void closeEvent(QCloseEvent *event);

private:
    struct Command
    {
        enum Type
        {
            New,
            Open,
            Save,
            Close,
            Quit
        };

        Command(Type type);
        Command(Type type, ScheduleWidget *widget);
        Command(Type type, ScheduleWidget *widget, const QString &argument);

        Type type;
        ScheduleWidget *widget;
        QString argument;
    };

private slots:
    void createFile();
    void openFile();
    void openSelectedFiles(const QStringList &fileNames);
    void saveFile();
    void saveFileAs();
    void saveAllFiles();
    void closeFile();
    void closeFileByIndex(int index);
    void closeAllFiles();
    void setBatchArgument(const QString &argument);
    void updateTabHeader(ScheduleWidget *widget);
    void updateWindowHeader();
    void showErrorMessage(const QString &text);
    void adjBatch(QList<ScheduleWidget *> w);

private:
    ScheduleWidget *createWidget();
    ScheduleWidget *currentWidget() const;
    ScheduleWidget *widget(int index) const;
    QList<ScheduleWidget *> all() const;
    QList<ScheduleWidget *> modified() const;
    void executeBatch();
    void adjustedBatch();

private:
    QTabWidget * const m_tabWidget;
    QList<Command> m_batch;
};

#endif // MAINWINDOW_H

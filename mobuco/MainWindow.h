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
    ~MainWindow();

protected:
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
    void closeFileDialog();
    void updateTabHeader(ScheduleWidget *widget);
    void updateWindowHeader();
    void showErrorMessage(const QString &text);

private:
    ScheduleWidget *createWidget();
    ScheduleWidget *currentWidget() const;
    ScheduleWidget *widget(int index) const;
    void executeBatch();

private:
    QTabWidget * const m_tabWidget;
    QList<Command> m_batch;
};

#endif // MAINWINDOW_H

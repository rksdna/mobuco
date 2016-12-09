#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QQueue>
#include <QMainWindow>

class QTabWidget;
class ScheduleWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    void appendItem(ScheduleWidget *item);
    void removeItem(ScheduleWidget *item);

protected:
    void hideEvent(QHideEvent *event);
    void closeEvent(QCloseEvent *event);

private slots:
    void createFile();
    void openFile();
    void saveFile();
    void saveFileAs();
    void saveAllFiles();
    void closeFile();
    void closeFileByIndex(int index);
    void closeAllFiles();
    void insertEntry();
    void removeEntries();
    void moveEntriesToTop();
    void moveEntriesUp();
    void moveEntriesDown();
    void moveEntriesToBottom();
    void about();
    void updateTabHeader(ScheduleWidget *item);
    void updateWindowHeader();

private:
    QList<ScheduleWidget *> items() const;
    QList<ScheduleWidget *> items(int index) const;
    ScheduleWidget *itemByIndex(int index) const;

private:
    QTabWidget * const m_widget;
};

#endif // MAINWINDOW_H

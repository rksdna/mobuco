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

private slots:
    void createFile();
    void openFile();
    void saveFile();
    void saveFileAs();
    void saveAllFiles();
    void closeFile();
    void closeFileByIndex(int index);
    void closeAllFiles();

    void updateTabHeader(ScheduleWidget *widget);
    void updateWindowHeader();

private:
    ScheduleWidget *currentWidget() const;

private:
    QTabWidget * const m_tabWidget;
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QQueue>
#include <QMainWindow>

class QTabWidget;
class ScheduleWidget;

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QWidget *parent = 0);
    QWidget *widget() const;

private:
    QWidget * const m_widget;
};

class SaveController : public Controller
{
    Q_OBJECT
public:
    explicit SaveController(const QList<ScheduleWidget *> &items, QWidget *parent = 0);
    ~SaveController();

public slots:
    void process();
    void save(const QString &fileName);

signals:
    void processed();
    void stopped();
    void saved(ScheduleWidget *item);

private:
    QString m_fileName;
    QList<ScheduleWidget *> m_items;
};

/*class CloseController : public Controller
{
    Q_OBJECT
public:
    explicit CloseController(const QList<ScheduleWidget *> items, QWidget *parent = 0);
    ~CloseController();

public slots:
    void process();
    void close(ScheduleWidget *item);
};*/


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);

protected:
    void hideEvent(QHideEvent *event);
    void closeEvent(QCloseEvent *event);

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

    void updateTabHeader(ScheduleWidget *item);
    void updateWindowHeader();

    void showOpenDialog();
    void showSaveDialog(const QString &fileName);
    void showPickDialog(const QList<ScheduleWidget *> items);
    void showErrorMessage(const QString &text);

private:
    ScheduleWidget *createItem();
    ScheduleWidget *currentItem() const;
    ScheduleWidget *item(int index) const;
    QList<ScheduleWidget *> items() const;

private:
    QTabWidget * const m_tabWidget;
};

#endif // MAINWINDOW_H

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

signals:
    void closeRequested();

protected:
    void hideEvent(QHideEvent *event);
    void closeEvent(QCloseEvent *event);

private slots:
    void newFile();
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
    void showErrorMessage(const QString &text);
    void openItems(const QStringList &fileNames);
    void queryItemsForSave();
    void setItemsForSave(const QList<ScheduleWidget *> &items);
    void queryItemFileName();
    void setItemFileName(const QString &fileName);
    void saveThenCloseItems();

private:
    void appendItem(ScheduleWidget *item);
    void saveItems(const QList<ScheduleWidget *> &items, bool askFileName);
    void closeItems(const QList<ScheduleWidget *> &items, bool exitAfterClose);
    QList<ScheduleWidget *> allItems() const;
    ScheduleWidget *itemByIndex(int index) const;

private:
    QTabWidget * const m_widget;
    QList<ScheduleWidget *> m_itemsForClose;
    QList<ScheduleWidget *> m_itemsForSave;
    QHash<ScheduleWidget *, QString> m_items;
    bool m_askFileName;
    bool m_exitAfterClose;
};

#endif // MAINWINDOW_H

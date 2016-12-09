#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QQueue>
#include <QMainWindow>

class QTabWidget;
class SchemeWidget;

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
    void insertItem();
    void removeItems();
    void moveItemsUp();
    void moveItemsDown();
    void about();
    void updateTabHeader(SchemeWidget *scheme);
    void updateWindowHeader();
    void showErrorMessage(const QString &text);
    void openSchemes(const QStringList &fileNames);
    void querySchemesForSave();
    void setSchemesForSave(const QList<SchemeWidget *> &schemes);
    void querySchemeFileName();
    void setFileName(const QString &fileName);
    void saveThenCloseSchemes();

private:
    void appendScheme(SchemeWidget *scheme);
    void saveSchemes(const QList<SchemeWidget *> &schemes, bool askFileName);
    void closeSchemes(const QList<SchemeWidget *> &schemes, bool exitAfterClose);
    QList<SchemeWidget *> schemes() const;
    SchemeWidget *schemeAt(int index) const;

private:
    struct SaveCloseContext
    {
        SaveCloseContext();
        void setSchemesForSave(const QList<SchemeWidget *> &schemes, bool askFileName);
        QList<SchemeWidget *> modifiedSchemes() const;
        SchemeWidget *schemeForSave() const;

        QList<SchemeWidget *> schemesForClose;
        QHash<SchemeWidget *, QString> schemesForSave;
        bool exitAfterClose;
    };

private:
    QTabWidget * const m_widget;
    SaveCloseContext m_context;
};

#endif // MAINWINDOW_H

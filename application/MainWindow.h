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
    void insertEntry();
    void removeEntries();
    void moveEntriesToTop();
    void moveEntriesUp();
    void moveEntriesDown();
    void moveEntriesToBottom();
    void about();
    void updateTabHeader(SchemeWidget *scheme);
    void updateWindowHeader();
    void showErrorMessage(const QString &text);
    void openSchemes(const QStringList &fileNames);
    void querySchemesForSave();
    void setSchemesForSave(const QList<SchemeWidget *> &schemes);
    void querySchemeFileName();
    void setSchemeFileName(const QString &fileName);
    void saveThenCloseSchemes();

private:
    void appendScheme(SchemeWidget *scheme);
    void saveSchemes(const QList<SchemeWidget *> &schemes, bool askFileName);
    void closeSchemes(const QList<SchemeWidget *> &schemes, bool exitAfterClose);
    QList<SchemeWidget *> allSchemes() const;
    SchemeWidget *schemeByIndex(int index) const;

private:
    QTabWidget * const m_widget;
    QList<SchemeWidget *> m_schemesForClose;
    QList<SchemeWidget *> m_schemesForSave;
    QHash<SchemeWidget *, QString> m_schemes;
    bool m_askFileName;
    bool m_exitAfterClose;
};

#endif // MAINWINDOW_H

#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>

class MainWindow;

class Command : public QObject
{
    Q_OBJECT
public:
    explicit Command(MainWindow *parent);

signals:
    void completed();
    void aborted();

protected:
    MainWindow *window() const;
    void showErrorMessage(const QString &text);

private:
    MainWindow * const m_window;
};

#endif // COMMAND_H

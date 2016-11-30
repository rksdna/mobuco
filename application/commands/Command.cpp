#include <QMessageBox>
#include "Command.h"
#include "MainWindow.h"

Command::Command(MainWindow *parent)
    : QObject(parent),
      m_window(parent)
{
    connect(this, &Command::completed, this, &Command::deleteLater);
    connect(this, &Command::aborted, this, &Command::deleteLater);
}

MainWindow *Command::window() const
{
    return m_window;
}

void Command::showErrorMessage(const QString &text)
{
    QMessageBox * const box = new QMessageBox(window());
    box->setText(text);
    box->setIcon(QMessageBox::Critical);
    connect(box, &QMessageBox::finished, box, &QMessageBox::deleteLater);

    box->open();
}

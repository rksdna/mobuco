#ifndef OPENCOMMAND_H
#define OPENCOMMAND_H

#include <QStringList>
#include "Command.h"

class OpenCommand : public Command
{
    Q_OBJECT
public:
    explicit OpenCommand(MainWindow *parent);
    void execute();

private slots:
    void process(const QStringList &fileNames);
};

#endif // OPENCOMMAND_H

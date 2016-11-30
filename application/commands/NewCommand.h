#ifndef NEWCOMMAND_H
#define NEWCOMMAND_H

#include "Command.h"

class NewCommand : public Command
{
    Q_OBJECT
public:
    explicit NewCommand(MainWindow *parent);
    void execute();
};

#endif // NEWCOMMAND_H

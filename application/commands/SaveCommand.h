#ifndef SAVECOMMAND_H
#define SAVECOMMAND_H

#include <QStringList>
#include "Command.h"

class SaveCommand : public Command
{
    Q_OBJECT
public:
    SaveCommand(const QList<ScheduleWidget *> &items, MainWindow *parent);
    void setAskFileName(bool askFileName);
    void execute();

signals:
    void itemSaved(ScheduleWidget *item);

private slots:
    void process(const QString &fileName);

private:
    bool m_askFileName;
    QList<ScheduleWidget *> m_items;
    QStringList m_errors;
};

#endif // SAVECOMMAND_H

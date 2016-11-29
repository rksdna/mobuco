#ifndef SAVESCHEDULEDIALOG_H
#define SAVESCHEDULEDIALOG_H

#include <QFileDialog>

class SaveScheduleDialog : public QFileDialog
{
    Q_OBJECT
public:
    SaveScheduleDialog(const QString &fileName, QWidget *parent = 0);

protected:
    void hideEvent(QHideEvent *event);
};

#endif // SAVESCHEDULEDIALOG_H

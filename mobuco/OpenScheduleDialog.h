#ifndef OPENSCHEDULEDIALOG_H
#define OPENSCHEDULEDIALOG_H

#include <QFileDialog>

class OpenScheduleDialog : public QFileDialog
{
    Q_OBJECT
public:
    OpenScheduleDialog(QWidget *parent = 0);

protected:
    void hideEvent(QHideEvent *event);
};

#endif // OPENSCHEDULEDIALOG_H

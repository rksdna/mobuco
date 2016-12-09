#ifndef SAVESCHEMEDIALOG_H
#define SAVESCHEMEDIALOG_H

#include <QFileDialog>

class SaveSchemeDialog : public QFileDialog
{
    Q_OBJECT
public:
    SaveSchemeDialog(const QString &fileName, QWidget *parent = 0);

protected:
    void hideEvent(QHideEvent *event);
};

#endif // SAVESCHEMEDIALOG_H

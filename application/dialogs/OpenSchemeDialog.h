#ifndef OPENSCHEMEDIALOG_H
#define OPENSCHEMEDIALOG_H

#include <QFileDialog>

class OpenSchemeDialog : public QFileDialog
{
    Q_OBJECT
public:
    OpenSchemeDialog(QWidget *parent = 0);

protected:
    void hideEvent(QHideEvent *event);
};

#endif // OPENSCHEMEDIALOG_H

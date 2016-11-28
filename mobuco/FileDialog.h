#ifndef FILEDIALOG_H
#define FILEDIALOG_H

#include <QFileDialog>

class FileDialog : public QFileDialog
{
    Q_OBJECT
public:
    enum Operation
    {
        OpenFiles,
        SaveFile
    };

public:
    FileDialog(Operation operation, QWidget *parent = 0);

protected:
    void hideEvent(QHideEvent *event);
};

#endif // FILEDIALOG_H

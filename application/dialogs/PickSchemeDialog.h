#ifndef PICKCHEDULEDIALOG_H
#define PICKSCHEMEDIALOG_H

#include <QDialog>

class SchemeWidget;
class PickSchemeModel;

class PickSchemeDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PickSchemeDialog(const QString &text, const QList<SchemeWidget *> &schemes, QWidget *parent = 0);

signals:
    void schemesSelected(const QList<SchemeWidget *> &schemes);

protected:
    void hideEvent(QHideEvent *event);

private slots:
    void yes();
    void none();
    void cancel();

private:
    PickSchemeModel * const m_model;
};

#endif // PICKSCHEMEDIALOG_H

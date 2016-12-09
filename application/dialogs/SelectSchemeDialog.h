#ifndef SELECTCHEDULEDIALOG_H
#define SELECTSCHEMEDIALOG_H

#include <QDialog>

class SchemeWidget;
class SelectSchemeModel;

class SelectSchemeDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SelectSchemeDialog(const QString &text, const QList<SchemeWidget *> &schemes, QWidget *parent = 0);

signals:
    void schemesSelected(const QList<SchemeWidget *> &schemes);

protected:
    void hideEvent(QHideEvent *event);

private slots:
    void yes();
    void none();
    void cancel();

private:
    SelectSchemeModel * const m_model;
};

#endif // SELECTSCHEMEDIALOG_H

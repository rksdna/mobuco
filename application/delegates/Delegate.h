#ifndef DELEGATE_H
#define DELEGATE_H

#include <QObject>

class Delegate : public QObject
{
    Q_OBJECT
public:
    explicit Delegate(QObject *parent = 0);
    virtual QWidget *createWidget(QWidget *parent) const = 0;
    virtual void destroyEditor(QWidget *editor) const = 0;
    virtual void setEditorData(QWidget *editor, const QVariant &editorData) const = 0;
    virtual QVariant editorData(QWidget *editor) const = 0;
    virtual QVariant displayData(const QVariant &value) const = 0;
};

class ComboDelegate : public Delegate
{
    Q_OBJECT
public:
    explicit ComboDelegate(const QString &items, QObject *parent = 0);
    QWidget *createWidget(QWidget *parent) const;
    void destroyEditor(QWidget *editor) const;
    void setEditorData(QWidget *editor, const QVariant &editorData) const;
    QVariant editorData(QWidget *editor) const;
    QVariant displayData(const QVariant &value) const;

private:
    const QString m_items;
};

#endif // DELEGATE_H

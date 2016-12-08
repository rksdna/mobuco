#ifndef DELEGATE_H
#define DELEGATE_H

#include <QMetaType>
#include <QSharedPointer>

class Delegate
{
public:
    virtual ~Delegate();
    virtual QWidget *createWidget(QWidget *parent) const = 0;
    virtual void destroyEditor(QWidget *editor) const = 0;
    virtual void setEditorData(QWidget *editor, const QVariant &data) const = 0;
    virtual QVariant editorData(QWidget *editor) const = 0;
};

typedef QSharedPointer<Delegate> DelegateSharedPointer;

Q_DECLARE_METATYPE(DelegateSharedPointer)

#endif // DELEGATE_H

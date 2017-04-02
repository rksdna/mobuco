#ifndef DELEGATE_H
#define DELEGATE_H

#include <QVariant>
#include <QMetaType>
#include <QSharedPointer>
#include <QCoreApplication>

class Delegate
{
    Q_DECLARE_TR_FUNCTIONS(Delegate)
public:
    typedef QSharedPointer<Delegate> Pointer;

public:
    template <typename CustomDelegate>
    static Pointer shared()
    {
        static Pointer delegate(new CustomDelegate);
        return delegate;
    }

public:
    virtual ~Delegate();

    virtual QVariant display(const QVariant &data) const = 0;
    virtual QVariant decoration(const QVariant &data) const = 0;
    virtual bool isEditable() const = 0;

    virtual QWidget *createEditor(QWidget *parent) const = 0;
    virtual void destroyEditor(QWidget *editor) const = 0;
    virtual void setEditorData(QWidget *editor, const QVariant &data) const = 0;
    virtual QVariant editorData(QWidget *editor) const = 0;
};

Q_DECLARE_METATYPE(Delegate::Pointer)

#endif // DELEGATE_H

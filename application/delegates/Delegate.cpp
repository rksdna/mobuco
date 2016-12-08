#include <QComboBox>
#include "Delegate.h"

Delegate::Delegate(QObject *parent)
    : QObject(parent)
{
}

ComboDelegate::ComboDelegate(const QString &items, QObject *parent)
    : Delegate(parent),
      m_items(items)
{
}

QWidget *ComboDelegate::createWidget(QWidget *parent) const
{
    QComboBox *e = new QComboBox(parent);
    e->addItems(m_items.split(";"));
    return e;
}

void ComboDelegate::destroyEditor(QWidget *editor) const
{
    editor->deleteLater();
}

void ComboDelegate::setEditorData(QWidget *editor, const QVariant &data) const
{
    QComboBox *e = static_cast<QComboBox *>(editor);
    e->setCurrentIndex(data.toInt());
}

QVariant ComboDelegate::editorData(QWidget *editor) const
{
    QComboBox *e = static_cast<QComboBox *>(editor);
    return e->currentIndex();
}

QVariant ComboDelegate::displayData(const QVariant &value) const
{
    return m_items.split(";").value(value.toInt());
}

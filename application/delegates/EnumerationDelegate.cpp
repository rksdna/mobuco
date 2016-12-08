#include <QComboBox>
#include "EnumerationDelegate.h"

EnumerationDelegate::EnumerationDelegate(const QString &items)
    : m_items(items)
{
}

QWidget *EnumerationDelegate::createWidget(QWidget *parent) const
{
    QComboBox *e = new QComboBox(parent);
    e->addItems(m_items.split(";"));
    return e;
}

void EnumerationDelegate::destroyEditor(QWidget *editor) const
{
    editor->deleteLater();
}

void EnumerationDelegate::setEditorData(QWidget *editor, const QVariant &data) const
{
    QComboBox *e = static_cast<QComboBox *>(editor);
    e->setCurrentIndex(data.toInt());
}

QVariant EnumerationDelegate::editorData(QWidget *editor) const
{
    QComboBox *e = static_cast<QComboBox *>(editor);
    return e->currentIndex();
}

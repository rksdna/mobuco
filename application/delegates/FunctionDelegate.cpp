#include <QComboBox>
#include "FunctionType.h"
#include "FunctionDelegate.h"

QVariant FunctionDelegate::display(const QVariant &data) const
{
    return toString(data.toInt());
}

QVariant FunctionDelegate::decoration(const QVariant &data) const
{
    Q_UNUSED(data)

    return QVariant();
}

bool FunctionDelegate::isEditable() const
{
    return true;
}

QWidget *FunctionDelegate::createEditor(QWidget *parent) const
{
    QComboBox * const widget = new QComboBox(parent);
    foreach (int code, FunctionType::types().keys())
        widget->addItem(toString(code), code);

    return widget;
}

void FunctionDelegate::destroyEditor(QWidget *editor) const
{
    editor->deleteLater();
}

void FunctionDelegate::setEditorData(QWidget *editor, const QVariant &data) const
{
    QComboBox * const widget = static_cast<QComboBox *>(editor);
    widget->setCurrentIndex(widget->findData(data));
}

QVariant FunctionDelegate::editorData(QWidget *editor) const
{
    QComboBox * const widget = static_cast<QComboBox *>(editor);
    return widget->currentData();
}

QString FunctionDelegate::toString(int code)
{
    const FunctionType * const type = FunctionType::types().value(code);
    return tr("%1 - %2").arg(type->code(), 2, 16, QChar('0')).arg(type->title());
}

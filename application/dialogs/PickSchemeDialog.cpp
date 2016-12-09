#include <QLabel>
#include <QSettings>
#include <QListView>
#include <QBoxLayout>
#include <QPushButton>
#include <QDialogButtonBox>
#include "PickSchemeModel.h"
#include "PickSchemeDialog.h"

PickSchemeDialog::PickSchemeDialog(const QString &text, const QList<SchemeWidget *> &schemes, QWidget *parent)
    : QDialog(parent),
      m_model(new PickSchemeModel(schemes, this))
{
    setWindowModality(Qt::ApplicationModal);

    QLabel * const label = new QLabel(text);

    QListView * const view = new QListView;
    view->setSelectionMode(QListView::NoSelection);
    view->setGridSize(QSize(24, 24));
    view->setUniformItemSizes(true);
    view->setModel(m_model);

    QDialogButtonBox * const box = new QDialogButtonBox(QDialogButtonBox::Yes | QDialogButtonBox::No | QDialogButtonBox::Cancel);
    connect(box->button(QDialogButtonBox::Yes), &QPushButton::clicked, this, &PickSchemeDialog::yes);
    connect(box->button(QDialogButtonBox::No), &QPushButton::clicked, this, &PickSchemeDialog::none);
    connect(box->button(QDialogButtonBox::Cancel), &QPushButton::clicked, this, &PickSchemeDialog::cancel);

    QBoxLayout * const layout = new QVBoxLayout(this);
    layout->addWidget(label);
    layout->addWidget(view);
    layout->addWidget(box);

    QSettings settings;
    restoreGeometry(settings.value("PickSchemeDialog/Geometry").toByteArray());
}

void PickSchemeDialog::yes()
{
    emit schemesSelected(m_model->selectedSchemes());
    accept();
}

void PickSchemeDialog::none()
{
    emit schemesSelected(QList<SchemeWidget *>());
    accept();
}

void PickSchemeDialog::cancel()
{
    reject();
}

void PickSchemeDialog::hideEvent(QHideEvent *event)
{
    QSettings settings;
    settings.setValue("PickSchemeDialog/Geometry", saveGeometry());

    QDialog::hideEvent(event);
}

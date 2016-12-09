#include <QLabel>
#include <QSettings>
#include <QListView>
#include <QBoxLayout>
#include <QPushButton>
#include <QDialogButtonBox>
#include "SelectSchemeModel.h"
#include "SelectSchemeDialog.h"

SelectSchemeDialog::SelectSchemeDialog(const QString &text, const QList<SchemeWidget *> &schemes, QWidget *parent)
    : QDialog(parent),
      m_model(new SelectSchemeModel(schemes, this))
{
    setWindowModality(Qt::ApplicationModal);

    QLabel * const label = new QLabel(text);

    QListView * const view = new QListView;
    view->setSelectionMode(QListView::NoSelection);
    view->setGridSize(QSize(24, 24));
    view->setUniformItemSizes(true);
    view->setModel(m_model);

    QDialogButtonBox * const box = new QDialogButtonBox(QDialogButtonBox::Yes | QDialogButtonBox::No | QDialogButtonBox::Cancel);
    connect(box->button(QDialogButtonBox::Yes), &QPushButton::clicked, this, &SelectSchemeDialog::yes);
    connect(box->button(QDialogButtonBox::No), &QPushButton::clicked, this, &SelectSchemeDialog::none);
    connect(box->button(QDialogButtonBox::Cancel), &QPushButton::clicked, this, &SelectSchemeDialog::cancel);

    QBoxLayout * const layout = new QVBoxLayout(this);
    layout->addWidget(label);
    layout->addWidget(view);
    layout->addWidget(box);

    QSettings settings;
    restoreGeometry(settings.value("SelectSchemeDialog/Geometry").toByteArray());
}

void SelectSchemeDialog::yes()
{
    emit schemesSelected(m_model->selectedSchemes());
    accept();
}

void SelectSchemeDialog::none()
{
    emit schemesSelected(QList<SchemeWidget *>());
    accept();
}

void SelectSchemeDialog::cancel()
{
    reject();
}

void SelectSchemeDialog::hideEvent(QHideEvent *event)
{
    QSettings settings;
    settings.setValue("SelectSchemeDialog/Geometry", saveGeometry());

    QDialog::hideEvent(event);
}

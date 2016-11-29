#include <QLabel>
#include <QSettings>
#include <QListView>
#include <QBoxLayout>
#include <QPushButton>
#include <QDialogButtonBox>
#include "PickScheduleModel.h"
#include "PickScheduleDialog.h"

PickScheduleDialog::PickScheduleDialog(const QString &text, const QList<ScheduleWidget *> &items, QWidget *parent)
    : QDialog(parent),
      m_model(new PickScheduleModel(items, this))
{
    QLabel * const label = new QLabel(text);

    QListView * const view = new QListView;
    view->setSelectionMode(QListView::NoSelection);
    view->setGridSize(QSize(24, 24));
    view->setUniformItemSizes(true);
    view->setModel(m_model);

    QDialogButtonBox * const box = new QDialogButtonBox(QDialogButtonBox::Yes | QDialogButtonBox::No | QDialogButtonBox::Cancel);
    connect(box->button(QDialogButtonBox::Yes), &QPushButton::clicked, this, &PickScheduleDialog::yes);
    connect(box->button(QDialogButtonBox::No), &QPushButton::clicked, this, &PickScheduleDialog::no);
    connect(box->button(QDialogButtonBox::Cancel), &QPushButton::clicked, this, &PickScheduleDialog::cancel);

    QBoxLayout * const layout = new QVBoxLayout(this);
    layout->addWidget(label);
    layout->addWidget(view);
    layout->addWidget(box);

    QSettings settings;
    restoreGeometry(settings.value("PickScheduleDialog/Geometry").toByteArray());
}

void PickScheduleDialog::yes()
{
    emit selected(m_model->selectedItems());
    accept();
}

void PickScheduleDialog::no()
{
    emit selected(QList<ScheduleWidget *>());
    accept();
}

void PickScheduleDialog::cancel()
{
    reject();
}

void PickScheduleDialog::hideEvent(QHideEvent *event)
{
    QSettings settings;
    settings.setValue("PickScheduleDialog/Geometry", saveGeometry());

    QDialog::hideEvent(event);
}

#include <QTreeView>
#include <QSettings>
#include <QBoxLayout>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QItemSelectionModel>
#include "ListModel.h"
#include "ListDialog.h"

ListDialog::ListDialog(const QList<ScheduleWidget *> &widgets, QWidget *parent) :
    QDialog(parent),
    m_model(new ListModel(widgets, this)),
    m_view(new QTreeView)
{
    connect(this, &ListDialog::finished, this, &ListDialog::deleteLater);

    m_view->setModel(m_model);
    m_view->setSelectionMode(QTreeView::MultiSelection);
    m_view->setSelectionBehavior(QTreeView::SelectRows);

    QDialogButtonBox *const box = new QDialogButtonBox(QDialogButtonBox::Cancel | QDialogButtonBox::Save | QDialogButtonBox::Discard);
    connect(box, &QDialogButtonBox::rejected, this, &ListDialog::reject);
    connect(box->button(QDialogButtonBox::Save), &QPushButton::clicked, this, &ListDialog::save);
    connect(box->button(QDialogButtonBox::Discard), &QPushButton::clicked, this, &ListDialog::discard);

    QBoxLayout * const layout = new QVBoxLayout(this);
    layout->addWidget(m_view);
    layout->addWidget(box);

    QSettings settings;
    restoreGeometry(settings.value("ListDialog/Geometry").toByteArray());
}

void ListDialog::hideEvent(QHideEvent *event)
{
    QSettings settings;
    settings.setValue("ListDialog/Geometry", saveGeometry());

    ListDialog::hideEvent(event);
}

void ListDialog::save()
{
    QList<ScheduleWidget *> result;
    foreach (const QModelIndex &index, m_view->selectionModel()->selectedRows())
        result.append(m_model->widget(index));

    emit selected(result);
    accept();
}

void ListDialog::discard()
{
    emit selected(QList<ScheduleWidget *>());
    accept();
}




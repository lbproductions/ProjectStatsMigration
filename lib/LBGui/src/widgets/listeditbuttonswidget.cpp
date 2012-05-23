#include "listeditbuttonswidget.h"

#include <QPushButton>
#include <QHBoxLayout>

namespace LBGui {

ListEditButtonsWidget::ListEditButtonsWidget(QWidget *parent) :
    QWidget(parent),
    m_addButton(new QPushButton(tr("Add"))),
    m_removeButton(new QPushButton(tr("Remove"))),
    m_editButton(new QPushButton(tr("Edit")))
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setSpacing(10);
    layout->addStretch();
    layout->addWidget(m_addButton);
    layout->addWidget(m_removeButton);
    layout->addWidget(m_editButton);
    setLayout(layout);

    connect(m_addButton, SIGNAL(clicked()), this, SIGNAL(addClicked()));
    connect(m_removeButton, SIGNAL(clicked()), this, SIGNAL(removeClicked()));
    connect(m_editButton, SIGNAL(clicked()), this, SIGNAL(editClicked()));
}

} // namespace LBGui

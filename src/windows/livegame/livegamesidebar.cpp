#include "livegamesidebar.h"

#include "sidebarpage.h"

#include <QVBoxLayout>
#include <QStackedWidget>
#include <QPushButton>
#include <QButtonGroup>
#include <QFile>
#include <QDebug>
#include <QStackedLayout>
#include <QApplication>

namespace LiveGameWindowNS {

LiveGameSidebar::LiveGameSidebar(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout *l = new QVBoxLayout(this);
    l->setContentsMargins(0,0,0,0);
    l->setSpacing(0);

    setPalette(QApplication::palette());

    m_stackedLayout = new QStackedLayout(l);

    QWidget *pageButtonsWidget = new QWidget(this);
    m_layoutPageButtons = new QHBoxLayout(pageButtonsWidget);
    pageButtonsWidget->setLayout(m_layoutPageButtons);
    l->addWidget(pageButtonsWidget);

    m_buttonGroup = new QButtonGroup(this);
    m_buttonGroup->setExclusive(true);
    connect(m_buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(setCurrentPage(int)));

//    QFile stylesheet2(":/stylesheets/livegamesidebar");
//    stylesheet2.open(QFile::ReadOnly);
//    setStyleSheet(stylesheet2.readAll());
//    stylesheet2.close();
//    setLayout(l);
}

void LiveGameSidebar::addPage(const QString &title, SidebarPage *sidebarPage)
{
    insertPage(m_stackedLayout->count(), title, sidebarPage);
}

void LiveGameSidebar::insertPage(int index, const QString &title, SidebarPage *sidebarPage)
{
    QPushButton *button = new QPushButton(title, this);
    button->setCheckable(true);
    button->setAttribute(Qt::WA_MacShowFocusRect, false);
    button->setFocusPolicy(Qt::NoFocus);
    int id = m_stackedLayout->addWidget(sidebarPage);
    m_buttonGroup->addButton(button, id);
    m_layoutPageButtons->insertWidget(index, button);
    m_sidebarPages.append(sidebarPage);
    button->setChecked(true);
    setCurrentPage(id);
}

void LiveGameSidebar::setCurrentPage(int id)
{
    m_stackedLayout->setCurrentIndex(id);
}

} // namespace LiveGameWindowNS

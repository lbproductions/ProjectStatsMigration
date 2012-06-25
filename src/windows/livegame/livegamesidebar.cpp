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

    QWidget *pageButtonsWidget = new QWidget(this);
    m_layoutPageButtons = new QHBoxLayout(pageButtonsWidget);
    m_layoutPageButtons->setContentsMargins(0,0,0,0);
    m_layoutPageButtons->setSpacing(12);
    pageButtonsWidget->setLayout(m_layoutPageButtons);
    l->addWidget(pageButtonsWidget);

    m_buttonGroup = new QButtonGroup(this);
    m_buttonGroup->setExclusive(true);
    connect(m_buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(setCurrentPage(int)));

    m_stackedLayout = new QStackedLayout(l);

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
    m_sidebarPages.insert(index, sidebarPage);
    button->setChecked(true);

    QFile stylesheet2(":/pushbutton/iphotodarktab/stylesheet");
    stylesheet2.open(QFile::ReadOnly);
    QString style = stylesheet2.readAll();

    if(index == m_stackedLayout->count() -1) {
        QLayoutItem *item = m_layoutPageButtons->itemAt(m_stackedLayout->count() - 2);
        if(item) {
            QWidget *rightmostButton = item->widget();
            if(rightmostButton) {
                rightmostButton->setStyleSheet(style);
            }
        }
        style += QLatin1String("QPushButton {margin-right: -1px; }");
    }

    button->setStyleSheet(style);

    stylesheet2.close();

    setCurrentPage(id);
}

int LiveGameSidebar::currentPage() const
{
    return m_stackedLayout->currentIndex();
}

void LiveGameSidebar::setCurrentPage(int id)
{
    m_buttonGroup->button(id)->setChecked(true);
    m_stackedLayout->setCurrentIndex(id);
}

} // namespace LiveGameWindowNS

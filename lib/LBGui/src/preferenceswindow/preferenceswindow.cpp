#include "preferenceswindow.h"

#include "preferencespage.h"

#include <QAction>
#include <QStackedWidget>

#ifdef Q_WS_MAC
#   include <QToolBar>
#endif

namespace LBGui {

/******************************************************************************
** PreferencesWindowPrivate
*/
class PreferencesWindowPrivate {
private:
    PreferencesWindowPrivate() :
        q_ptr(0)
    {}

    void addPage(PreferencesPage *page);
    void setCurrentPage(PreferencesPage *page);

    QStackedWidget *centralWidget;
    QList<PreferencesPage *> pages;

#ifdef Q_WS_MAC
    QToolBar *toolBar;
#endif

    PreferencesWindow *q_ptr;
    Q_DECLARE_PUBLIC(PreferencesWindow)
};

#ifdef Q_WS_MAC

void PreferencesWindowPrivate::addPage(PreferencesPage *page)
{
    Q_Q(PreferencesWindow);
    centralWidget->addWidget(page);
    toolBar->addAction(page->action());
    QObject::connect(page, SIGNAL(selected()), q, SLOT(onPageSelected()));
    pages.append(page);
    setCurrentPage(page);
}

void PreferencesWindowPrivate::setCurrentPage(PreferencesPage *page)
{
    Q_Q(PreferencesWindow);
    foreach(PreferencesPage *p, pages) {
        if(p == page) {
            p->action()->setChecked(true);
            centralWidget->setCurrentWidget(p);
            q->setWindowTitle(page->name());
        }
        else {
            p->action()->setChecked(false);
        }
    }
}

#elif defined Q_WS_WIN
#   error PreferencesWindowPrivate::addPage has to be implemented on windows.
#endif

/******************************************************************************
** PreferencesWindow
*/
PreferencesWindow::PreferencesWindow(QWidget *parent) :
    QMainWindow(parent),
    d_ptr(new PreferencesWindowPrivate)
{
    Q_D(PreferencesWindow);
    d->q_ptr = this;

    d->centralWidget = new QStackedWidget(this);
    setCentralWidget(d->centralWidget);

    d->toolBar = new QToolBar(this);
    d->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    d->toolBar->setIconSize(QSize(32,32));
    d->toolBar->setStyleSheet("QToolBar { padding: 0px; margin: 0px }");
    d->toolBar->setContentsMargins(0,0,0,-4);
    setUnifiedTitleAndToolBarOnMac(true);
    addToolBar(d->toolBar);

    setAttribute(Qt::WA_DeleteOnClose);
}

PreferencesWindow::~PreferencesWindow()
{
}

void PreferencesWindow::addPage(PreferencesPage *page)
{
    Q_D(PreferencesWindow);
    d->addPage(page);
}

void PreferencesWindow::setCurrentPage(PreferencesPage *page)
{
    Q_D(PreferencesWindow);
    d->setCurrentPage(page);
}

void PreferencesWindow::onPageSelected()
{
    PreferencesPage *page = static_cast<PreferencesPage *>(sender());
    setCurrentPage(page);
}


} // namespace LBGui

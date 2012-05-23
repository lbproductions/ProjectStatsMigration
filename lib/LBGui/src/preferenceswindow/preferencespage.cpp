#include "preferencespage.h"

#include "preferenceswindow.h"

#include <QAction>

namespace LBGui {

/******************************************************************************
** PreferencesWindowPrivate
*/
class PreferencesPagePrivate {
private:
    PreferencesPagePrivate() :
        q_ptr(0)
    {}

    QAction *action;
    QString name;

    PreferencesPage *q_ptr;
    Q_DECLARE_PUBLIC(PreferencesPage)
};

/******************************************************************************
** PreferencesPage
*/
PreferencesPage::PreferencesPage(PreferencesWindow *parent) :
    QWidget(parent),
    d_ptr(new PreferencesPagePrivate)
{
    Q_D(PreferencesPage);
    d->action = new QAction(this);
    d->action->setCheckable(true);
    connect(d->action ,SIGNAL(triggered()), this, SIGNAL(selected()));
}

PreferencesPage::~PreferencesPage()
{
}

QString PreferencesPage::name() const
{
    Q_D(const PreferencesPage);
    return d->name;
}

void PreferencesPage::setName(const QString &name)
{
    Q_D(PreferencesPage);
    d->name = name;
    d->action->setIconText(name);
    d->action->setText(name);
}

void PreferencesPage::setIcon(const QIcon &icon)
{
    Q_D(PreferencesPage);
    d->action->setIcon(icon);
}

QAction *PreferencesPage::action() const
{
    Q_D(const PreferencesPage);
    return d->action;
}

} // namespace LBGui

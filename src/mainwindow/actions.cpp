#include "actions.h"

#include "controller.h"

#include <LBGui/LBGui.h>


namespace MainWindowNS {

Actions::Actions(Controller *controller) :
    QObject(controller),
    m_controller(controller)
{
    // connect changes (like open files, or selected text etc) to the updateActions slot
    //connect(controller, SIGNAL(somethingChanged()), this, SLOT(updateActions()));

    m_checkForUpdatesAction = new LBGui::Action(this);
    m_checkForUpdatesAction->setText(tr("&Check for updates..."));
    m_checkForUpdatesAction->setMenuRole(QAction::ApplicationSpecificRole);
    connect(m_checkForUpdatesAction, SIGNAL(triggered()), m_controller, SLOT(checkForUpdates()));

    m_showPreferencesAction = new LBGui::Action(this);
    m_showPreferencesAction->setText(tr("&Preferences..."));
    m_showPreferencesAction->setShortcut(QKeySequence::Preferences);
    connect(m_showPreferencesAction, SIGNAL(triggered()), m_controller, SLOT(showPreferences()));

    m_newGameAction = new LBGui::Action(this);
    m_newGameAction->setText(tr("&New game..."));
    m_newGameAction->setShortcut(QKeySequence::New);
    m_newGameAction->setIcon(QIcon(":/graphics/icons/mainwindow/newgame"));
    connect(m_newGameAction, SIGNAL(triggered()), m_controller, SLOT(newGame()));
}

LBGui::Action *Actions::checkForUpdatesAction() const
{
    return m_checkForUpdatesAction;
}

LBGui::Action *Actions::showPreferencesAction() const
{
    return m_showPreferencesAction;
}

LBGui::Action *Actions::newGameAction() const
{
    return m_newGameAction;
}

void Actions::updateActions()
{
    // enable actions, based on some conditions (like open files, or selected text etc)
}

} // namespace MainWindowNS

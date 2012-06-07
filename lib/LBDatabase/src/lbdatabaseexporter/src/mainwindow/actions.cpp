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


    m_showPreferencesAction = new LBGui::Action(this);
    m_showPreferencesAction->setText(tr("&Preferences..."));
    m_showPreferencesAction->setShortcut(QKeySequence::Preferences);
    connect(m_showPreferencesAction, SIGNAL(triggered()), m_controller, SLOT(showPreferences()));
}

LBGui::Action *Actions::showPreferencesAction() const
{
    return m_showPreferencesAction;
}

void Actions::updateActions()
{
    // enable actions, based on some conditions (like open files, or selected text etc)
}

} // namespace MainWindowNS

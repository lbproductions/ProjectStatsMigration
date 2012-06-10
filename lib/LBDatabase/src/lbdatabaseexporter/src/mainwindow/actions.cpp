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

    m_addAttributeAction = new LBGui::Action(this);
    m_addAttributeAction->setText(tr("Add &Attribute..."));
    m_addAttributeAction->setEnabled(false);
    m_addAttributeAction->setIcon(QIcon(":/icons/actions/attribute_add"));
    connect(m_addAttributeAction, SIGNAL(triggered()), m_controller, SLOT(addAttribute()));

    m_addFunctionAction = new LBGui::Action(this);
    m_addFunctionAction->setText(tr("Add &Function..."));
    m_addFunctionAction->setEnabled(false);
    m_addFunctionAction->setIcon(QIcon(":/icons/actions/function_add"));
    connect(m_addFunctionAction, SIGNAL(triggered()), m_controller, SLOT(addFunction()));

    m_addRelationAction = new LBGui::Action(this);
    m_addRelationAction->setText(tr("Add &Relation..."));
    m_addRelationAction->setEnabled(false);
    m_addRelationAction->setIcon(QIcon(":/icons/actions/relation_add"));
    connect(m_addRelationAction, SIGNAL(triggered()), m_controller, SLOT(addRelation()));

    m_editAttributeAction = new LBGui::Action(this);
    m_editAttributeAction->setText(tr("Edit A&ttribute..."));
    m_editAttributeAction->setEnabled(false);
    m_editAttributeAction->setIcon(QIcon(":/icons/actions/attribute_edit"));
    connect(m_editAttributeAction, SIGNAL(triggered()), m_controller, SLOT(editAttribute()));

    m_editFunctionAction = new LBGui::Action(this);
    m_editFunctionAction->setText(tr("Edit &Function..."));
    m_editFunctionAction->setEnabled(false);
    m_editFunctionAction->setIcon(QIcon(":/icons/actions/function_edit"));
    connect(m_editFunctionAction, SIGNAL(triggered()), m_controller, SLOT(editFunction()));

    m_editRelationAction = new LBGui::Action(this);
    m_editRelationAction->setText(tr("Edit &Relation..."));
    m_editRelationAction->setEnabled(false);
    m_editRelationAction->setIcon(QIcon(":/icons/actions/relation_edit"));
    connect(m_editRelationAction, SIGNAL(triggered()), m_controller, SLOT(editRelation()));
}

LBGui::Action *Actions::showPreferencesAction() const
{
    return m_showPreferencesAction;
}

LBGui::Action *Actions::addAttributeAction() const
{
    return m_addAttributeAction;
}

LBGui::Action *Actions::addFunctionAction() const
{
    return m_addFunctionAction;
}

LBGui::Action *Actions::addRelationAction() const
{
    return m_addRelationAction;
}

LBGui::Action *Actions::editAttributeAction() const
{
    return m_editAttributeAction;
}

LBGui::Action *Actions::editFunctionAction() const
{
    return m_editFunctionAction;
}

LBGui::Action *Actions::editRelationAction() const
{
    return m_editRelationAction;
}

void Actions::updateActions()
{
    // enable actions, based on some conditions (like open files, or selected text etc)
}

} // namespace MainWindowNS

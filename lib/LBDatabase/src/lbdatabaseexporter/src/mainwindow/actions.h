#ifndef MAINWINDOW_ACTIONS_H
#define MAINWINDOW_ACTIONS_H

#include <QObject>

namespace LBGui {
class Action;
}

namespace MainWindowNS {

class Controller;

class Actions : public QObject
{
    Q_OBJECT
public:
    explicit Actions(Controller *controller);

    LBGui::Action *showPreferencesAction() const;

    LBGui::Action *openStorageAction() const;

    LBGui::Action *addAttributeAction() const;
    LBGui::Action *addFunctionAction() const;
    LBGui::Action *addRelationAction() const;

    LBGui::Action *editAttributeAction() const;
    LBGui::Action *editFunctionAction() const;
    LBGui::Action *editRelationAction() const;

public slots:
    void updateActions();

private:
    Controller *m_controller;

    LBGui::Action *m_showPreferencesAction;

    LBGui::Action *m_openStorageAction;

    LBGui::Action *m_addAttributeAction;
    LBGui::Action *m_addFunctionAction;
    LBGui::Action *m_addRelationAction;

    LBGui::Action *m_editAttributeAction;
    LBGui::Action *m_editFunctionAction;
    LBGui::Action *m_editRelationAction;

};

} // namespace MainWindowNS

#endif // MAINWINDOW_ACTIONS_H

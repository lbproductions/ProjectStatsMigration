#ifndef MAINWINDOW_SIDEBAR_H
#define MAINWINDOW_SIDEBAR_H

#include <LBGui/LBGui.h>

namespace MainWindowNS {

class Controller;

class Sidebar : public LBGui::Sidebar
{
    Q_OBJECT
public:
    Sidebar(Controller *controller);

private slots:
    void onCategorieChanged(::LBGui::SidebarChildCategorie*);

private:
    Controller *m_controller;
};

} // namespace MainWindowNS

#endif // MAINWINDOW_SIDEBAR_H

#include "sidebar.h"

#include "mainwindow.h"
#include "controller.h"

namespace MainWindowNS {

Sidebar::Sidebar(Controller *controller) :
    LBGui::Sidebar(controller->mainWindow()),
    m_controller(controller)
{
    connect(this, SIGNAL(categorieChanged(::LBGui::SidebarChildCategorie*)), this, SLOT(onCategorieChanged(::LBGui::SidebarChildCategorie*)));
}

void Sidebar::onCategorieChanged(LBGui::SidebarChildCategorie *cat)
{
    if(cat->view()) {
        m_controller->showWidget(cat->view());
        cat->view()->activated();
    }
}

} // namespace MainWindowNS

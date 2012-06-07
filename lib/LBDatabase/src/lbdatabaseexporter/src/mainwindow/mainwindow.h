#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <LBGui/LBGui.h>

namespace LBDatabase {
class Storage;
class EntityType;
}

namespace MainWindowNS {
class Controller;
class Sidebar;
}

class MainWindow : public LBGui::MainWindow
{
public:
    MainWindow();

    void closeEvent(QCloseEvent *event);

    void setStorage(LBDatabase::Storage *storage);

private:
    void setupCentralWidgets();
    void setupSidebar();
    void setupMenuBar();
    void setupToolBar();

    void addEntityTypeCategoriesRecursive(LBDatabase::EntityType *entityType, LBGui::SidebarChildCategorie *parentCategorie);

    MainWindowNS::Controller *m_controller;
    MainWindowNS::Sidebar *m_sidebar;

    LBDatabase::Storage *m_storage;
};

#endif // MAINWINDOW_H

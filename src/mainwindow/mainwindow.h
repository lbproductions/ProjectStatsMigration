#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <LBGui/LBGui.h>

namespace MainWindowNS {
class Controller;
class Sidebar;
class ListView;
}

class MainWindow : public LBGui::MainWindow
{
public:
    MainWindow(QWidget *parent = 0);

    void closeEvent(QCloseEvent *event);

    MainWindowNS::Controller *controller() const;

    void setup();

private:
    void setupCentralWidgets();
    void setupSidebar();
    void setupMenuBar();
    void setupToolBar();

    MainWindowNS::Controller *m_controller;
    MainWindowNS::Sidebar *m_sidebar;

    MainWindowNS::ListView *m_gamesView;
    MainWindowNS::ListView *m_playersView;
};

#endif // MAINWINDOW_H

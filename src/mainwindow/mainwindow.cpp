#include "mainwindow.h"

#include "actions.h"
#include "controller.h"
#include "sidebar.h"
#include "model/storage.h"
#include "model/gamescontext.h"
#include "model/playerscontext.h"
#include "views/listview.h"

#include <QCloseEvent>
#include <QStackedWidget>

MainWindow::MainWindow(QWidget *parent) :
    LBGui::MainWindow(parent),
    m_controller(new MainWindowNS::Controller(this)),
    m_sidebar(new MainWindowNS::Sidebar(m_controller))
{
    setSettingsName(QLatin1String("MainWindow"));
    setTitle(tr("Project Stats"));

    //save and restore window size and position
    setSaveSettings(true);
    restoreSettings();
}

void MainWindow::setupCentralWidgets()
{
    // add possible central widgets:
    m_gamesView = new MainWindowNS::ListView(m_controller, this);
    m_gamesView->setContext(m_controller->storage()->gamesContext());
    m_playersView = new MainWindowNS::ListView(m_controller, this);
    m_playersView->setContext(m_controller->storage()->playersContext());
    centralViewStackedWidget()->addWidget(m_gamesView);
    centralViewStackedWidget()->addWidget(m_playersView);

    // add a grey background as starting widget
    LBGui::BackgroundWidget *background = new LBGui::BackgroundWidget(centralViewStackedWidget());
    background->setStyle(LBGui::BackgroundWidget::Gray);
    centralViewStackedWidget()->addWidget(background);
    centralViewStackedWidget()->setCurrentWidget(background);
}

void MainWindow::setupSidebar()
{
    //add categories to the sidebar

    m_sidebar->addParentCategorie(tr("Library"));
    m_sidebar->addChildCategorie(0,tr("Games"))->setView(m_gamesView);
    m_sidebar->addChildCategorie(0,tr("Players"))->setView(m_playersView);

    m_sidebar->expandAll();

    setLeftSideBar(m_sidebar);
}

void MainWindow::setupMenuBar()
{
    //add actions to the menu bar
    menuBar()->addAction(tr("&File"), m_controller->actions()->newGameAction());
    menuBar()->addAction(tr("&File"), m_controller->actions()->checkForUpdatesAction());
    menuBar()->addAction(tr("&File"), m_controller->actions()->showPreferencesAction());
    menuBar()->addAction(tr("&File"), m_controller->actions()->connectToServerAction());

    menuBar()->addMenu(menuBar()->windowMenu());
    menuBar()->addMenu(menuBar()->helpMenu());
    menuBar()->addWindow(this);
}

void MainWindow::setupToolBar()
{
    LBGui::ToolBar *toolBar = new LBGui::ToolBar(this);

    toolBar->addAction(m_controller->actions()->newGameAction());

    setUnifiedTitleAndToolBarOnMac(true);
    addToolBar(toolBar);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(m_controller->close()) {
        saveSettings();
        event->accept();
    }
    else {
        event->ignore();
    }
}

MainWindowNS::Controller *MainWindow::controller() const
{
    return m_controller;
}

void MainWindow::setup()
{
    setupCentralWidgets();
    setupSidebar();
    setupMenuBar();
    setupToolBar();
}

#include "mainwindow.h"

#include "actions.h"
#include "controller.h"
#include "sidebar.h"
#include "views/entitytypeview.h"

#include <LBDatabase/LBDatabase.h>

#include <QCloseEvent>
#include <QStackedWidget>

MainWindow::MainWindow() :
    LBGui::MainWindow(),
    m_controller(new MainWindowNS::Controller(this)),
    m_sidebar(new MainWindowNS::Sidebar(m_controller))
{
    setSettingsName(QLatin1String("MainWindow"));
    setTitle(tr("LBDatabase Editor"));

    setupSidebar();
    setupCentralWidgets();
    setupMenuBar();
    setupToolBar();

    //save and restore window size and position
    setSaveSettings(true);
    restoreSettings();
}

void MainWindow::setupCentralWidgets()
{
    // add possible central widgets:
    //centralViewStackedWidget()->addWidget(new QWidget(centralViewStackedWidget()));

    // add a grey background as starting widget
    LBGui::BackgroundWidget *background = new LBGui::BackgroundWidget(centralViewStackedWidget());
    background->setStyle(LBGui::BackgroundWidget::Gray);
    centralViewStackedWidget()->addWidget(background);
    centralViewStackedWidget()->setCurrentWidget(background);
}

void MainWindow::setupSidebar()
{
    //add categories to the sidebar

    m_sidebar->addParentCategorie(tr("Contexts"));
    m_sidebar->addParentCategorie(tr("EntityTypes"));

    m_sidebar->expandAll();

    setLeftSideBar(m_sidebar);
}

void MainWindow::setupMenuBar()
{
    //add actions to the menu bar
    menuBar()->addAction(tr("&File"), m_controller->actions()->openStorageAction());
    menuBar()->addSeparator(tr("&File"));
    menuBar()->addAction(tr("&File"), m_controller->actions()->addAttributeAction());
    menuBar()->addAction(tr("&File"), m_controller->actions()->addFunctionAction());
    menuBar()->addAction(tr("&File"), m_controller->actions()->addRelationAction());
    menuBar()->addAction(tr("&File"), m_controller->actions()->editAttributeAction());
    menuBar()->addAction(tr("&File"), m_controller->actions()->editFunctionAction());
    menuBar()->addAction(tr("&File"), m_controller->actions()->editRelationAction());
    menuBar()->addSeparator(tr("&File"));
    menuBar()->addAction(tr("&File"), m_controller->actions()->exportAction());
    menuBar()->addAction(tr("&File"), m_controller->actions()->showPreferencesAction());

    menuBar()->addMenu(menuBar()->windowMenu());
    menuBar()->addMenu(menuBar()->helpMenu());
    menuBar()->addWindow(this);
}

void MainWindow::setupToolBar()
{
    LBGui::ToolBar *toolBar = new LBGui::ToolBar(this);
    toolBar->setIconSize(QSize(32,32));

    //add actions to the tool bar
    toolBar->addAction(m_controller->actions()->addAttributeAction());
    toolBar->addAction(m_controller->actions()->editAttributeAction());
    QWidget* spacer = new QWidget(toolBar);
    spacer->setFixedWidth(50);
    toolBar->addWidget(spacer);
    toolBar->addAction(m_controller->actions()->addFunctionAction());
    toolBar->addAction(m_controller->actions()->editFunctionAction());
    spacer = new QWidget(toolBar);
    spacer->setFixedWidth(50);
    toolBar->addWidget(spacer);
    toolBar->addAction(m_controller->actions()->addRelationAction());
    toolBar->addAction(m_controller->actions()->editRelationAction());
    spacer = new QWidget(toolBar);
    spacer->setFixedWidth(50);
    toolBar->addWidget(spacer);
    toolBar->addAction(m_controller->actions()->exportAction());


    setUnifiedTitleAndToolBarOnMac(true);
    addToolBar(toolBar);
}

void MainWindow::addEntityTypeCategoriesRecursive(LBDatabase::EntityType *entityType, LBGui::SidebarChildCategorie *parentCategorie)
{
    LBGui::SidebarChildCategorie* item;
    if(parentCategorie) {
        item = new LBGui::SidebarChildCategorie(entityType->displayName());
        parentCategorie->appendRow(item);
    }
    else {
        item = m_sidebar->addChildCategorie(1, entityType->displayName());
    }

    MainWindowNS::EntityTypeView *view = new MainWindowNS::EntityTypeView(this);
    view->setEntityType(entityType);
    item->setView(view);

    foreach(LBDatabase::EntityType *child, entityType->childEntityTypes()) {
        addEntityTypeCategoriesRecursive(child, item);
    }
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

void MainWindow::setStorage(LBDatabase::Storage *storage)
{
    m_storage = storage;

    foreach(LBDatabase::Context *context, storage->contexts()) {
        addEntityTypeCategoriesRecursive(context->baseEntityType(), 0);
    }
}

MainWindowNS::Controller *MainWindow::controller() const
{
    return m_controller;
}

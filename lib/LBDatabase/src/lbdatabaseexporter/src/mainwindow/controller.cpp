#include "controller.h"

#include "actions.h"
#include "mainwindow.h"
#include "views/entitytypeview.h"

#include <LBDatabase/LBDatabase.h>
#include <LBGui/LBGui.h>

#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include <QSettings>

namespace MainWindowNS {

Controller::Controller(MainWindow *mainWindow) :
    QObject(mainWindow),
    m_mainWindow(mainWindow),
    m_actions(new Actions(this))
{

}

MainWindow *Controller::mainWindow() const
{
    return m_mainWindow;
}

Actions *Controller::actions()
{
    return m_actions;
}

bool Controller::close()
{
    //somehow confirm the closing of the main window
    return true;
}

void Controller::example()
{
    QMessageBox msg;
    msg.setText("Example");
    msg.exec();

    emit somethingChanged();
}

void Controller::showPreferences()
{
    LBGui::PreferencesWindow *window = new LBGui::PreferencesWindow;

    window->show();
}

void Controller::addAttribute()
{
    static_cast<MainWindowNS::EntityTypeView *>(m_mainWindow->centralWidget())->addAttribute();
}

void Controller::addFunction()
{
    static_cast<MainWindowNS::EntityTypeView *>(m_mainWindow->centralWidget())->addFunction();
}

void Controller::addRelation()
{
    static_cast<MainWindowNS::EntityTypeView *>(m_mainWindow->centralWidget())->addRelation();
}

void Controller::editAttribute()
{
    static_cast<MainWindowNS::EntityTypeView *>(m_mainWindow->centralWidget())->editAttribute();
}

void Controller::editFunction()
{
    static_cast<MainWindowNS::EntityTypeView *>(m_mainWindow->centralWidget())->editFunction();
}

void Controller::editRelation()
{
    static_cast<MainWindowNS::EntityTypeView *>(m_mainWindow->centralWidget())->editRelation();
}

void Controller::showWidget(QWidget *widget)
{
    m_mainWindow->setCentralWidget(widget);
    emit somethingChanged();
}

} // namespace MainWindowNS

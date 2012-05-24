#include "controller.h"

#include "actions.h"
#include "mainwindow.h"

#include "../model/projectstatsstorage.h"
#include "../model/game.h"
#include "../model/doppelkopflivegame.h"
#include "../preferences/updaterpreferences.h"
#include "../wizards/newgame/newgamewizard.h"
#include "../windows/livegame/livegamewindow.h"

#include <widgets/graphs/dokolivegamegraphview.h>

#ifdef Q_WS_MAC
#   include "../misc/sparkleupdater.h"
#elif defined Q_WS_WIN
#   include "../misc/winsparkleupdater.h"
#endif

#include <LBDatabase/LBDatabase.h>
#include <LBGui/LBGui.h>

#include <QApplication>
#include <QDebug>
#include <QDesktopServices>
#include <QMessageBox>
#include <QSettings>

namespace MainWindowNS {

Controller::Controller(MainWindow *mainWindow) :
    QObject(mainWindow),
    m_mainWindow(mainWindow),
    m_actions(new Actions(this))
{
#ifdef Q_WS_MAC
    m_updater = new SparkleUpdater(APPCASTURL"/AppCast_mac.xml");
#elif defined Q_WS_WIN
    m_updater = new WinSparkleUpdater("APPCASTURL/AppCast_win.xml");
#endif

    if(m_updater)
        UpdaterPreferences::initializeUpdater(m_updater);

    QString storageLocation = QDesktopServices::storageLocation(QDesktopServices::DataLocation).append("/storage.lbstorage");
    qDebug() << storageLocation;
    m_storage = new ProjectStatsStorage(this);
    m_storage->setDriver(
                new LBDatabase::LocalStorageDriver(
                    storageLocation,
                    m_storage)
                );
    m_storage->open();
}

MainWindow *Controller::mainWindow() const
{
    return m_mainWindow;
}

Actions *Controller::actions() const
{
    return m_actions;
}

ProjectStatsStorage *Controller::storage() const
{
    return m_storage;
}

bool Controller::close()
{
    //somehow confirm the closing of the main window
    return true;
}

void Controller::checkForUpdates()
{
    if(m_updater)
        m_updater->checkForUpdates();
}

void Controller::showPreferences()
{
    LBGui::PreferencesWindow *window = new LBGui::PreferencesWindow;
    UpdaterPreferences *updaterPreferences = new UpdaterPreferences(m_updater, window);
    connect(updaterPreferences, SIGNAL(checkForUpdatesRequested()), this, SLOT(checkForUpdates()));

    window->addPage(updaterPreferences);

    window->show();
}

void Controller::newGame()
{
    Wizards::NewGameWizard *wizard = new Wizards::NewGameWizard(m_storage, m_mainWindow);
    wizard->show();
}

void Controller::showWidget(QWidget *widget)
{
    m_mainWindow->setCentralWidget(widget);
    emit somethingChanged();
}

void Controller::openEntityWindow(LBDatabase::Entity *entity)
{
    if(entity->entityType()->id() == DoppelkopfLiveGame::EntityTypeId) {
        LiveGame *game = static_cast<LiveGame *>(entity);
        LiveGameWindow *window = new LiveGameWindow();
        window->setGame(game);
        window->show();

        Gui::Graphs::DokoLiveGameGraphView *graph = new Gui::Graphs::DokoLiveGameGraphView(window);
        graph->setLiveGame(game);
        window->setCentralWidget(graph);
    }
}

} // namespace MainWindowNS

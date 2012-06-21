#include "controller.h"

#include "actions.h"
#include "mainwindow.h"

#include <model/storage.h>
#include <model/doppelkopflivegame.h>
#include <model/gamescontext.h>

#include <model/roundscontext.h>
#include <model/round.h>
#include <model/doppelkopfround.h>

#include <preferences/updaterpreferences.h>
#include <wizards/newgame/newgamewizard.h>
#include <windows/livegame/doppelkopf/dokolivegamewindow.h>

#ifdef Q_OS_MAC
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
#include <QElapsedTimer>

namespace MainWindowNS {

Controller::Controller(MainWindow *mainWindow) :
    QObject(mainWindow),
    m_mainWindow(mainWindow),
    m_actions(new Actions(this))
{
#ifdef Q_OS_MAC
    m_updater = new SparkleUpdater(APPCASTURL"/AppCast_mac.xml");
#elif defined Q_WS_WIN
    m_updater = new WinSparkleUpdater("APPCASTURL/AppCast_win.xml");
#endif

    if(m_updater)
        UpdaterPreferences::initializeUpdater(m_updater);

    QString storageLocation = QDesktopServices::storageLocation(QDesktopServices::DataLocation).append("/storage.lbstorage");
    QElapsedTimer timer;
    timer.start();
    m_storage = new Storage(this);
    m_storage->setDriver(
                new LBDatabase::LocalStorageDriver(
                    storageLocation,
                    m_storage)
                );
    if(!m_storage->open()) {
        QMessageBox msgBox;
        msgBox.setText(tr("The storage could not be opened! ProjectStats will be terminated"));
        msgBox.setInformativeText(QDesktopServices::storageLocation(QDesktopServices::DataLocation).append("/storage.lbstorage"));
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        exit(-1);
    }
    qDebug() << "Opening the storage took "+QString::number(timer.elapsed())+"ms.";

    openEntityWindow(m_storage->gamesContext()->game(38));
}

MainWindow *Controller::mainWindow() const
{
    return m_mainWindow;
}

Actions *Controller::actions() const
{
    return m_actions;
}

Storage *Controller::storage() const
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
        DoppelkopfLiveGame *game = static_cast<DoppelkopfLiveGame *>(entity);
        DokoLiveGameWindow *window = new DokoLiveGameWindow();
        window->setDoppelkopfLiveGame(game);
        window->show();
    }
}

} // namespace MainWindowNS

#include "dokolivegamewindow.h"

#include "centralwidget.h"
#include "newrounddialog.h"
#include "newschmeissereidialog.h"
#include "../adddrinkwidget.h"
#include "statisticssidebar.h"

#include <model/doppelkopflivegame.h>
#include <model/doppelkopfround.h>
#include <model/storage.h>

#include <QAction>

DokoLiveGameWindow::DokoLiveGameWindow(QWidget *parent) :
    LiveGameWindow(parent),
    m_doppelkopfLiveGame(0)
{
    setupToolBar();

    m_centralWidget = new DokoLiveGameWindowNS::CentralWidget(this);
    setCentralWidget(m_centralWidget);
}

void DokoLiveGameWindow::setupToolBar()
{
    m_actionShowSchmeissereiDialog = new QAction(QIcon(":/graphics/icons/livegame/schmeisserei"),tr("Schmeisserei"), this);
    connect(m_actionShowSchmeissereiDialog,SIGNAL(triggered()),this,SLOT(showNewSchmeissereiDialog()));
    addToolBarAction(m_actionShowSchmeissereiDialog, MiddleToolBarPosition);
}

void DokoLiveGameWindow::setDoppelkopfLiveGame(DoppelkopfLiveGame *doppelkopfLiveGame)
{
    if(doppelkopfLiveGame == m_doppelkopfLiveGame)
        return;

    m_doppelkopfLiveGame = doppelkopfLiveGame;

    m_actionShowSchmeissereiDialog->setEnabled(m_doppelkopfLiveGame->doko_mitSchmeisserei());
    m_centralWidget->setDoppelkopfLiveGame(m_doppelkopfLiveGame);

    setLiveGame(m_doppelkopfLiveGame);
}

void DokoLiveGameWindow::reflectState(LiveGame::State state)
{
    m_actionShowSchmeissereiDialog->setEnabled(true);

    switch(state) {
    case LiveGame::Paused:
    case LiveGame::Finished:
        m_actionShowSchmeissereiDialog->setEnabled(false);
        break;

    case LiveGame::Running:
    default:
        break;
    }

    LiveGameWindow::reflectState(state);
}

void DokoLiveGameWindow::showNewSchmeissereiDialog()
{
    DokoLiveGameWindowNS::NewSchmeissereiDialog dialog;
    dialog.setDoppelkopfRound(static_cast<DoppelkopfRound *>(m_doppelkopfLiveGame->rounds().last()));
    dialog.exec();
}

void DokoLiveGameWindow::showNewRoundDialog()
{
    DokoLiveGameWindowNS::NewRoundDialog dialog;
    dialog.setDoppelkopfRound(static_cast<DoppelkopfRound *>(m_doppelkopfLiveGame->rounds().last()));
    dialog.exec();
}

void DokoLiveGameWindow::showEndGameDialog()
{
}

void DokoLiveGameWindow::showAddDrinkDialog()
{
    int oldPage = m_centralWidget->statisticsSidebar()->currentPage();
    LiveGameWindowNS::AddDrinkWidget addDrinkDialog(static_cast<Storage *>(m_doppelkopfLiveGame->entityType()->context()->storage()));
    m_centralWidget->statisticsSidebar()->setCurrentPage(1);
    addDrinkDialog.exec();
    m_centralWidget->statisticsSidebar()->setCurrentPage(oldPage);

}

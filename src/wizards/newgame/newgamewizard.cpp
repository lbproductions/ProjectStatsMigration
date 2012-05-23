#include "newgamewizard.h"

#include "livegamegeneraloptionswidget.h"
#include "livedokogameoptionswidget.h"

#include "../../model/game.h"
#include "../../model/doppelkopflivegame.h"
#include "../../model/place.h"
#include "../../model/projectstatsstorage.h"

#include <QDebug>
#include <QMessageBox>

namespace Wizards {

NewGameWizard::NewGameWizard(ProjectStatsStorage *storage, QWidget *parent) :
    QWizard(parent),
    m_storage(storage)
{
    initializeWidget();
    setModal(true);

    connect(this,SIGNAL(accepted()),this,SLOT(on_accepted()));

    setAttribute(Qt::WA_DeleteOnClose);
    setWizardStyle(QWizard::AeroStyle);
    setWindowModality(Qt::WindowModal);
    setButtonText(QWizard::FinishButton,"Create Game");
}

void NewGameWizard::initializeWidget()
{
    this->setWindowTitle(tr("New Game"));

    this->setOption(QWizard::NoCancelButton,false);
    this->setOption(QWizard::NoBackButtonOnStartPage,true);

    m_liveGameGeneralOptionsWidget = new NewGame::LiveGameGeneralOptionsWidget(this);
    m_liveDokoGameOptionsWidget = new NewGame::LiveDokoGameOptionsWidget(this);

    this->setPage(Page_LiveGameGeneralOptions, m_liveGameGeneralOptionsWidget);
    this->setPage(Page_LiveGameDokoOptions, m_liveDokoGameOptionsWidget);
}

ProjectStatsStorage *NewGameWizard::storage() const
{
    return m_storage;
}

void NewGameWizard::on_accepted()
{
    DoppelkopfLiveGame *game = m_storage->gamesContext()->createDoppelkopfGame();
    m_liveGameGeneralOptionsWidget->selectedPlace()->addGame(game);

    int position = 1;
    foreach(Player *player, m_liveGameGeneralOptionsWidget->selectedPlayers()) {
        game->addPlayer(player);
        game->setPosition(player, position++);
    }
    game->setDoko_mitHochzeit(field("doko_mitHochzeit").toBool());
    game->setDoko_mitSolo(field("doko_mitSolo").toBool());
    game->setDoko_mitTrumpfabgabe(field("doko_mitTrumpfabgabe").toBool());
    game->setDoko_mitSchweinerei(field("doko_mitSchweinerei").toBool());
    game->setDoko_mitSchmeisserei(field("doko_mitSchmeisserei").toBool());

    game->setDoko_mitPflichtsolo(field("doko_mitPflichtsolo").toBool());
    game->setDoko_mitBubensolo(field("doko_mitBubenSolo").toBool());
    game->setDoko_mitDamensolo(field("doko_mitDamenSolo").toBool());
    game->setDoko_mitFarbsolo(field("doko_mitFarbsolo").toBool());
    game->setDoko_mitFleischlos(field("doko_mitFleischlos").toBool());
    game->setDoko_mitTrumpfsolo(field("doko_mitTrumpfsolo").toBool());
    game->setDoko_mitSchwarzsolo(field("doko_mitSchwarzsolo").toBool());

    game->setDoko_mitFuenfKoenige(field("doko_mitFuenfKoenige").toBool());
    game->setDoko_mitZuWenigTrumpf(field("doko_mitZuWenigTrumpf").toBool());
    game->setDoko_mitNeunzigPunkte(field("doko_mitNeunzigPunkte").toBool());
    game->setDoko_mitTrumpfabgabeSchmeisserei(field("doko_mitTrumpfabgabeSchmeisserei").toBool());


//    Database::Game* game = 0;
//    if(field("isLive").toBool())
//    {
//        Database::LiveGame *livegame = 0;
//        QString type = field("live_type").toString();
//        if(type == Database::DokoLiveGame::TYPE)
//        {
//            livegame = createDokoLiveGame();
//        }
//        else if(type == "Skat")
//        {

//        }

//        Database::Games::instance()->insertRow(livegame);

//        livegame->startNextRound();

//        livegame->date->setValue(QDateTime::currentDateTime());

//        QPointer<Database::Place> place = m_liveGameGeneralOptionsWidget->selectedPlace();
//        livegame->siteId->setValue(place->id());

//        foreach(Database::Player *player, m_liveGameGeneralOptionsWidget->selectedPlayers())
//        {
//            livegame->addPlayer(player);
//        }

//        game = livegame;
//    }
//    else
//    {

//    }

//    game->rowWindow()->show();
}

//Database::DokoLiveGame *NewGameWizard::createDokoLiveGame()
//{
//    Database::DokoLiveGame *game = new Database::DokoLiveGame(
//field("doko_mitHochzeit").toBool(),
//field("doko_mitSolo").toBool(),
//field("doko_mitTrumpfabgabe").toBool(),
//field("doko_mitSchweinerei").toBool(),
//field("doko_mitSchmeisserei").toBool(),

//field("doko_mitPflichtsolo").toBool(),
//field("doko_mitBubenSolo").toBool(),
//field("doko_mitDamenSolo").toBool(),
//field("doko_mitFarbsolo").toBool(),
//field("doko_mitFleischlos").toBool(),
//field("doko_mitTrumpfsolo").toBool(),
//field("doko_mitSchwarzsolo").toBool(),

//field("doko_mitFuenfKoenige").toBool(),
//field("doko_mitZuWenigTrumpf").toBool(),
//field("doko_mitNeunzigPunkte").toBool(),
//field("doko_mitTrumpfabgabeSchmeisserei").toBool()
//);

//    return game;
//}

}

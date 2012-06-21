#include "newrounddialog.h"
#include "ui_newrounddialog.h"

#include <model/storage.h>
#include <model/doppelkopfround.h>
#include <model/doppelkopflivegame.h>
#include <model/roundscontext.h>

namespace DokoLiveGameWindowNS {

NewRoundDialog::NewRoundDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewRoundDialog),
    m_doppelkopfRound(0)
{
    ui->setupUi(this);

    ui->buttonGroup->setId(ui->pushButtonNormal, 0);
    ui->buttonGroup->setId(ui->pushButtonHochzeit, 1);
    ui->buttonGroup->setId(ui->pushButtonSolo, 2);
    ui->buttonGroup->setId(ui->pushButtonTrumpfabgabe, 3);

    ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(false);
    connect(ui->comboBoxNormalRe1, SIGNAL(currentIndexChanged(int)), this, SLOT(checkNormalRoundContents()));
    connect(ui->comboBoxNormalRe2, SIGNAL(currentIndexChanged(int)), this, SLOT(checkNormalRoundContents()));
    connect(ui->spinBoxNormalPoints,SIGNAL(valueChanged(int)), this, SLOT(checkNormalRoundContents()));

    connect(ui->comboBoxHochzeitHochzeit, SIGNAL(currentIndexChanged(int)), this, SLOT(checkHochzeitRoundContents()));
    connect(ui->comboBoxHochzeitFellow, SIGNAL(currentIndexChanged(int)), this, SLOT(checkHochzeitRoundContents()));
    connect(ui->spinBoxHochzeitPoints,SIGNAL(valueChanged(int)),this, SLOT(checkHochzeitRoundContents()));

    connect(ui->comboBoxSoloPlayer, SIGNAL(currentIndexChanged(int)), this, SLOT(checkSoloRoundContents()));
    connect(ui->comboBoxSoloType, SIGNAL(currentIndexChanged(int)), this, SLOT(checkSoloRoundContents()));
    connect(ui->spinBoxSoloPoints,SIGNAL(valueChanged(int)), this, SLOT(checkSoloRoundContents()));

    connect(ui->comboBoxTrumpfabgabePlayer, SIGNAL(currentIndexChanged(int)), this, SLOT(checkTrumpfabgabeRoundContents()));
    connect(ui->comboBoxTrumpfabgabeAccept, SIGNAL(currentIndexChanged(int)), this, SLOT(checkTrumpfabgabeRoundContents()));
    connect(ui->spinBoxTrumpfabgabePoints,SIGNAL(valueChanged(int)),this, SLOT(checkTrumpfabgabeRoundContents()));

    connect(ui->buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(setCurrentPage(int)));

    connect(ui->buttonBox->button(QDialogButtonBox::Save), SIGNAL(clicked()), this, SLOT(save()));
}

NewRoundDialog::~NewRoundDialog()
{
    delete ui;
}

void NewRoundDialog::setDoppelkopfRound(DoppelkopfRound *round)
{
    if(!round || m_doppelkopfRound == round)
        return;

    DoppelkopfLiveGame *game = static_cast<DoppelkopfLiveGame *>(round->game());

    m_doppelkopfRound = round;
    ui->comboBoxNormalRe1->addPlayers(round->currentPlayingPlayers());
    ui->comboBoxNormalRe1->setCurrentPlayer(round->rePlayer1());
    ui->comboBoxNormalRe2->addPlayers(round->currentPlayingPlayers());
    ui->comboBoxNormalRe2->setCurrentPlayer(round->rePlayer2());
    ui->comboBoxNormalSchweine->setEnabled(game->doko_mitSchweinerei());
    ui->comboBoxNormalSchweine->addPlayers(round->currentPlayingPlayers());
    ui->comboBoxNormalSchweine->setCurrentPlayer(round->schweinereiPlayer());

    ui->comboBoxHochzeitHochzeit->addPlayers(round->currentPlayingPlayers());
    ui->comboBoxHochzeitHochzeit->setCurrentPlayer(round->hochzeitPlayer());
    ui->comboBoxHochzeitFellow->addPlayers(round->currentPlayingPlayers());
    ui->comboBoxHochzeitFellow->setCurrentPlayer(round->rePlayer2());
    ui->comboBoxHochzeitSchweine->setEnabled(game->doko_mitSchweinerei());
    ui->comboBoxHochzeitSchweine->addPlayers(round->currentPlayingPlayers());
    ui->comboBoxHochzeitSchweine->setCurrentPlayer(round->schweinereiPlayer());

    ui->comboBoxSoloPlayer->addPlayers(round->currentPlayingPlayers());
    ui->comboBoxSoloPlayer->setCurrentPlayer(round->dokoSoloPlayer());
    ui->comboBoxSoloSchweine->setEnabled(game->doko_mitSchweinerei());
    ui->comboBoxSoloSchweine->addPlayers(round->currentPlayingPlayers());
    ui->comboBoxSoloSchweine->setCurrentPlayer(round->schweinereiPlayer());
    ui->checkBoxSoloPflicht->setEnabled(game->doko_mitPflichtsolo());
    ui->comboBoxSoloType->addItems(game->allowedSoli());
    if(game->allowedSoli().indexOf(round->doko_soloType()) >= 0)
        ui->comboBoxSoloType->setCurrentIndex(game->allowedSoli().indexOf(round->doko_soloType()));
    else
        ui->comboBoxSoloType->setCurrentIndex(0);

    ui->comboBoxTrumpfabgabePlayer->addPlayers(round->currentPlayingPlayers());
    ui->comboBoxTrumpfabgabePlayer->setCurrentPlayer(round->trumpfabgabePlayer());
    ui->comboBoxTrumpfabgabeAccept->addPlayers(round->currentPlayingPlayers());
    ui->comboBoxTrumpfabgabeAccept->setCurrentPlayer(round->rePlayer2());
    ui->comboBoxTrumpfabgabeSchweine->setEnabled(game->doko_mitSchweinerei());
    ui->comboBoxTrumpfabgabeSchweine->addPlayers(round->currentPlayingPlayers());
    ui->comboBoxTrumpfabgabeSchweine->setCurrentPlayer(round->schweinereiPlayer());

    ui->pushButtonSolo->setEnabled(!game->allowedSoli().isEmpty());
    ui->pushButtonHochzeit->setEnabled(game->doko_mitHochzeit());
    ui->pushButtonTrumpfabgabe->setEnabled(game->doko_mitTrumpfabgabe());

    ui->comboBoxWinner->addItem("Re");
    ui->comboBoxWinner->addItem("Contra");

    ui->comboBoxTrumpfabgabeWinner->addItem("Re");
    ui->comboBoxTrumpfabgabeWinner->addItem("Contra");

    ui->comboBoxSoloWinner->addItem("Re");
    ui->comboBoxSoloWinner->addItem("Contra");

    ui->comboBoxHochzeitWinner->addItem("Re");
    ui->comboBoxHochzeitWinner->addItem("Contra");
}

void NewRoundDialog::setCurrentPage(int index)
{
    ui->stackedWidget->setCurrentIndex(index);

    switch(index) {
    case 0:
        checkNormalRoundContents();
        break;
    case 1:
        checkHochzeitRoundContents();
        break;
    case 2:
        checkSoloRoundContents();
        break;
    case 3:
        checkTrumpfabgabeRoundContents();
        break;
    default:
        ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(false);
    }
}

void NewRoundDialog::checkNormalRoundContents()
{
    ui->comboBoxNormalRe1->addPlayers(m_doppelkopfRound->currentPlayingPlayers());
    ui->comboBoxNormalRe2->addPlayers(m_doppelkopfRound->currentPlayingPlayers());

    if(ui->comboBoxNormalRe1->currentPlayer()) {
        ui->comboBoxNormalRe2->removePlayer(ui->comboBoxNormalRe1->currentPlayer());
    }
    if(ui->comboBoxNormalRe2->currentPlayer()) {
        ui->comboBoxNormalRe1->removePlayer(ui->comboBoxNormalRe2->currentPlayer());
    }

    ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(ui->comboBoxNormalRe1->currentPlayer() &&
                                                              ui->comboBoxNormalRe2->currentPlayer());

    if(ui->spinBoxNormalPoints->value() == 0)
    {
        ui->comboBoxWinner->setEnabled(true);
    }
    else
    {
        ui->comboBoxWinner->setEnabled(false);

        if(ui->spinBoxNormalPoints->value() > 0)
        {
            ui->comboBoxWinner->setCurrentIndex(ui->comboBoxWinner->findText("Re"));
        }
        if(ui->spinBoxNormalPoints->value() < 0)
        {
            ui->comboBoxWinner->setCurrentIndex(ui->comboBoxWinner->findText("Contra"));
        }
    }
}

void NewRoundDialog::checkHochzeitRoundContents()
{
    ui->comboBoxHochzeitHochzeit->addPlayers(m_doppelkopfRound->currentPlayingPlayers());
    ui->comboBoxHochzeitFellow->addPlayers(m_doppelkopfRound->currentPlayingPlayers());

    if(ui->comboBoxHochzeitHochzeit->currentPlayer()) {
        ui->comboBoxHochzeitFellow->removePlayer(ui->comboBoxHochzeitHochzeit->currentPlayer());
    }
    if(ui->comboBoxHochzeitFellow->currentPlayer()) {
        ui->comboBoxHochzeitHochzeit->removePlayer(ui->comboBoxHochzeitFellow->currentPlayer());
    }

    ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(ui->comboBoxHochzeitHochzeit->currentPlayer() &&
                                                              ui->comboBoxHochzeitFellow->currentPlayer());

    if(ui->spinBoxHochzeitPoints->value() == 0)
    {
        ui->comboBoxHochzeitWinner->setEnabled(true);
    }
    else
    {
        ui->comboBoxHochzeitWinner->setEnabled(false);

        if(ui->spinBoxHochzeitPoints->value() > 0)
        {
            ui->comboBoxHochzeitWinner->setCurrentIndex(ui->comboBoxHochzeitWinner->findText("Re"));
        }
        if(ui->spinBoxHochzeitPoints->value() < 0)
        {
            ui->comboBoxHochzeitWinner->setCurrentIndex(ui->comboBoxHochzeitWinner->findText("Contra"));
        }
    }
}

void NewRoundDialog::checkSoloRoundContents()
{
    DoppelkopfLiveGame *game = static_cast<DoppelkopfLiveGame *>(m_doppelkopfRound->game());
    if(!game->doko_mitPflichtsolo() ||
            (ui->comboBoxSoloPlayer->currentPlayer() && game->hasPflichtsolo(ui->comboBoxSoloPlayer->currentPlayer()))) {
        ui->checkBoxSoloPflicht->setChecked(false);
        ui->checkBoxSoloPflicht->setEnabled(false);
    }
    else {
        ui->checkBoxSoloPflicht->setChecked(true);
        ui->checkBoxSoloPflicht->setEnabled(true);
    }

    if(ui->comboBoxSoloType->currentText() == "Trumpf") {
        ui->comboBoxSoloSchweine->setEnabled(true);
    }
    else {
        ui->comboBoxSoloSchweine->setEnabled(false);
        ui->comboBoxSoloSchweine->setCurrentPlayer(0);
    }

    ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(ui->comboBoxSoloPlayer->currentPlayer());

    if(ui->spinBoxSoloPoints->value() == 0)
    {
        ui->comboBoxSoloWinner->setEnabled(true);
    }
    else
    {
        ui->comboBoxSoloWinner->setEnabled(false);

        if(ui->spinBoxSoloPoints->value() > 0)
        {
            ui->comboBoxSoloWinner->setCurrentIndex(ui->comboBoxSoloWinner->findText("Re"));
        }
        if(ui->spinBoxSoloPoints->value() < 0)
        {
            ui->comboBoxSoloWinner->setCurrentIndex(ui->comboBoxSoloWinner->findText("Contra"));
        }
    }
}

void NewRoundDialog::checkTrumpfabgabeRoundContents()
{
    ui->comboBoxTrumpfabgabePlayer->addPlayers(m_doppelkopfRound->currentPlayingPlayers());
    ui->comboBoxTrumpfabgabeAccept->addPlayers(m_doppelkopfRound->currentPlayingPlayers());

    if(ui->comboBoxTrumpfabgabePlayer->currentPlayer()) {
        ui->comboBoxTrumpfabgabeAccept->removePlayer(ui->comboBoxTrumpfabgabePlayer->currentPlayer());
    }
    if(ui->comboBoxTrumpfabgabeAccept->currentPlayer()) {
        ui->comboBoxTrumpfabgabePlayer->removePlayer(ui->comboBoxTrumpfabgabeAccept->currentPlayer());
    }

    ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(ui->comboBoxTrumpfabgabePlayer->currentPlayer() &&
                                                              ui->comboBoxTrumpfabgabeAccept->currentPlayer());

    if(ui->spinBoxTrumpfabgabePoints->value() == 0)
    {
        ui->comboBoxTrumpfabgabeWinner->setEnabled(true);
    }
    else
    {
        ui->comboBoxTrumpfabgabeWinner->setEnabled(false);

        if(ui->spinBoxTrumpfabgabePoints->value() > 0)
        {
            ui->comboBoxTrumpfabgabeWinner->setCurrentIndex(ui->comboBoxTrumpfabgabeWinner->findText("Re"));
        }
        if(ui->spinBoxTrumpfabgabePoints->value() < 0)
        {
            ui->comboBoxTrumpfabgabeWinner->setCurrentIndex(ui->comboBoxTrumpfabgabeWinner->findText("Contra"));
        }
    }
}

void NewRoundDialog::save()
{
    switch(ui->buttonGroup->checkedId()) {
    case 0:
        saveNormalRound();
        break;
    case 1:
        saveHochzeitRound();
        break;
    case 2:
        saveSoloRound();
        break;
    case 3:
        saveTrumpfabgabeRound();
        break;
    default:
        break;
    }
}

void NewRoundDialog::saveNormalRound()
{
    m_doppelkopfRound->setRePlayer1(ui->comboBoxNormalRe1->currentPlayer());
    m_doppelkopfRound->setRePlayer2(ui->comboBoxNormalRe2->currentPlayer());
    m_doppelkopfRound->setComment(ui->textEditNormalComment->toPlainText());
    if(ui->comboBoxNormalSchweine->currentPlayer())
        m_doppelkopfRound->setSchweinereiPlayer(ui->comboBoxNormalSchweine->currentPlayer());

    foreach(Player *p, m_doppelkopfRound->currentPlayingPlayers()) {
        if(p == ui->comboBoxNormalRe1->currentPlayer() ||
                p == ui->comboBoxNormalRe2->currentPlayer()) {
            m_doppelkopfRound->setPoints(p, ui->spinBoxNormalPoints->value());
        }
        else {
            m_doppelkopfRound->setPoints(p, -ui->spinBoxNormalPoints->value());
        }
    }
    m_doppelkopfRound->setState(Round::Finished);
    if(ui->comboBoxWinner->currentText() == "Re")
    {
        m_doppelkopfRound->setWinner(DoppelkopfRound::Re);
    }
    else
    {
        m_doppelkopfRound->setWinner(DoppelkopfRound::Contra);
    }

    DoppelkopfLiveGame *game = static_cast<DoppelkopfLiveGame *>(m_doppelkopfRound->game());
    game->addRound();
}

void NewRoundDialog::saveHochzeitRound()
{
    m_doppelkopfRound->setHochzeitPlayer(ui->comboBoxHochzeitHochzeit->currentPlayer());
    m_doppelkopfRound->setRePlayer1(ui->comboBoxHochzeitHochzeit->currentPlayer());
    m_doppelkopfRound->setRePlayer2(ui->comboBoxHochzeitFellow->currentPlayer());
    m_doppelkopfRound->setComment(ui->textEditHochzeitComment->toPlainText());
    if(ui->comboBoxHochzeitSchweine->currentPlayer())
        m_doppelkopfRound->setSchweinereiPlayer(ui->comboBoxHochzeitSchweine->currentPlayer());

    foreach(Player *p, m_doppelkopfRound->currentPlayingPlayers()) {
        if(p == ui->comboBoxHochzeitHochzeit->currentPlayer() ||
                p == ui->comboBoxHochzeitFellow->currentPlayer()) {
            m_doppelkopfRound->setPoints(p, ui->spinBoxHochzeitPoints->value());
        }
        else {
            m_doppelkopfRound->setPoints(p, -ui->spinBoxHochzeitPoints->value());
        }
    }
    m_doppelkopfRound->setState(Round::Finished);

    if(ui->comboBoxHochzeitWinner->currentText() == "Re")
    {
        m_doppelkopfRound->setWinner(DoppelkopfRound::Re);
    }
    else
    {
        m_doppelkopfRound->setWinner(DoppelkopfRound::Contra);
    }

    DoppelkopfLiveGame *game = static_cast<DoppelkopfLiveGame *>(m_doppelkopfRound->game());
    game->addRound();
}

void NewRoundDialog::saveSoloRound()
{
    m_doppelkopfRound->setDokoSoloPlayer(ui->comboBoxSoloPlayer->currentPlayer());
    m_doppelkopfRound->setRePlayer1(ui->comboBoxSoloPlayer->currentPlayer());
    m_doppelkopfRound->setComment(ui->textEditSoloComment->toPlainText());
    if(ui->comboBoxSoloSchweine->currentPlayer())
        m_doppelkopfRound->setSchweinereiPlayer(ui->comboBoxSoloSchweine->currentPlayer());

    m_doppelkopfRound->setDoko_soloType(ui->comboBoxSoloType->currentText());
    m_doppelkopfRound->setDoko_soloPflicht(ui->checkBoxSoloPflicht->isChecked());

    foreach(Player *p, m_doppelkopfRound->currentPlayingPlayers()) {
        if(p == ui->comboBoxSoloPlayer->currentPlayer()) {
            m_doppelkopfRound->setPoints(p, 3 * ui->spinBoxSoloPoints->value());
        }
        else {
            m_doppelkopfRound->setPoints(p, -ui->spinBoxSoloPoints->value());
        }
    }
    m_doppelkopfRound->setState(Round::Finished);

    if(ui->comboBoxSoloWinner->currentText() == "Re")
    {
        m_doppelkopfRound->setWinner(DoppelkopfRound::Re);
    }
    else
    {
        m_doppelkopfRound->setWinner(DoppelkopfRound::Contra);
    }

    DoppelkopfLiveGame *game = static_cast<DoppelkopfLiveGame *>(m_doppelkopfRound->game());
    game->addRound();
}

void NewRoundDialog::saveTrumpfabgabeRound()
{
    m_doppelkopfRound->setTrumpfabgabePlayer(ui->comboBoxTrumpfabgabePlayer->currentPlayer());
    m_doppelkopfRound->setRePlayer1(ui->comboBoxTrumpfabgabePlayer->currentPlayer());
    m_doppelkopfRound->setRePlayer2(ui->comboBoxTrumpfabgabeAccept->currentPlayer());
    m_doppelkopfRound->setComment(ui->textEditTrumpfabgabeComment->toPlainText());
    if(ui->comboBoxTrumpfabgabeSchweine->currentPlayer())
        m_doppelkopfRound->setSchweinereiPlayer(ui->comboBoxTrumpfabgabeSchweine->currentPlayer());

    foreach(Player *p, m_doppelkopfRound->currentPlayingPlayers()) {
        if(p == ui->comboBoxTrumpfabgabePlayer->currentPlayer() ||
                p == ui->comboBoxTrumpfabgabeAccept->currentPlayer()) {
            m_doppelkopfRound->setPoints(p, ui->spinBoxTrumpfabgabePoints->value());
        }
        else {
            m_doppelkopfRound->setPoints(p, -ui->spinBoxTrumpfabgabePoints->value());
        }
    }
    m_doppelkopfRound->setState(Round::Finished);

    if(ui->comboBoxTrumpfabgabeWinner->currentText() == "Re")
    {
        m_doppelkopfRound->setWinner(DoppelkopfRound::Re);
    }
    else
    {
        m_doppelkopfRound->setWinner(DoppelkopfRound::Contra);
    }

    DoppelkopfLiveGame *game = static_cast<DoppelkopfLiveGame *>(m_doppelkopfRound->game());
    game->addRound();
}

}

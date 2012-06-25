#include "newschmeissereidialog.h"
#include "ui_newschmeissereidialog.h"

#include <model/doppelkopfround.h>
#include <model/doppelkopflivegame.h>
#include <model/storage.h>
#include <model/schmeisserei.h>
#include <model/schmeissereiencontext.h>

#include <QPushButton>

namespace DokoLiveGameWindowNS {

NewSchmeissereiDialog::NewSchmeissereiDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewSchmeissereiDialog),
    m_round(0)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);

    this->setObjectName("dialog");
    this->setStyleSheet("QWidget#dialog { background-image: url(:/general/background_linen); } QLabel { color: white; }");

    on_comboBoxPlayer_currentIndexChanged(0);
}

NewSchmeissereiDialog::~NewSchmeissereiDialog()
{
    delete ui;
}

void NewSchmeissereiDialog::setDoppelkopfRound(DoppelkopfRound *round)
{
    m_round = round;
    ui->comboBoxPlayer->addPlayers(round->currentPlayingPlayers());
    ui->comboBoxType->addItems(static_cast<DoppelkopfLiveGame*>(round->game())->allowedSchmeissereien());
}

void NewSchmeissereiDialog::on_buttonBox_accepted()
{
    Storage *psstorage = static_cast<Storage *>(m_round->entityType()->context()->storage());
    Schmeisserei *s = psstorage->schmeissereienContext()->createSchmeisserei();
    s->setPlayer(ui->comboBoxPlayer->currentPlayer());
    s->setType(ui->comboBoxType->currentText());
    s->setRound(m_round);
    accept();
}

} // namespace DokoLiveGameWindowNS



void DokoLiveGameWindowNS::NewSchmeissereiDialog::on_comboBoxPlayer_currentIndexChanged(int index)
{
    Q_UNUSED(index)
    ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(ui->comboBoxPlayer->currentPlayer() != 0);
}

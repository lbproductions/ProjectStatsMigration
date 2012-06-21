#include "statisticsgeneralpage.h"

#include "statisticssidebar.h"

#include <model/doppelkopflivegame.h>
#include <model/doppelkopfround.h>
#include <model/player.h>

#include <LBGui/LBGui.h>

#include <QLabel>
#include <QFont>
#include <QTime>
#include <QTimer>

namespace DokoLiveGameWindowNS {

StatisticsGeneralPage::StatisticsGeneralPage(StatisticsSidebar *parent) :
    SidebarPage(parent)
{
    QVBoxLayout *l = new QVBoxLayout(this);
    setLayout(l);

    m_spacer = new QWidget(this);
    m_spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_currentTimeLabel = addLabel(tr("Current Time"), QTime::currentTime().toString("h:mm:ss"));
    m_lengthLabel = addLabel(tr("Length"), QString());
    m_dealerLabel = addLabel(tr("Dealer"), QString());
    m_numberOfRoundsLabel = addLabel(tr("Number of rounds"), QString());
    m_reVsContraLabel = addLabel(tr("Re vs. Contra"), QString());
    m_hochzeitenLabel = addLabel(tr("Hochzeiten"), QString());
    m_soliLabel = addLabel(tr("Soli"), QString());
    m_pflichsoliLabel = addLabel(tr("Pflichtsoli"), QString());
    m_trumpfabgabenLabel = addLabel(tr("Trumpfabgaben"), QString());
    m_schmeissereienLabel = addLabel(tr("Schmeissereien"), QString());
    m_schweinereienLabel = addLabel(tr("Schweinereien"), QString());

    QTimer *timer = new QTimer(this);
    timer->setInterval(1000);
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(updateCurrentTimeLabel()));

    l->addWidget(m_spacer);
}

void StatisticsGeneralPage::setDoppelkopfLiveGame(DoppelkopfLiveGame *game)
{
    m_game = game;
    updateLengthLabel();
    updateDealerLabel();
}

void StatisticsGeneralPage::updateCurrentTimeLabel()
{
    m_currentTimeLabel->setText(QTime::currentTime().toString("h:mm:ss"));
}

void StatisticsGeneralPage::updateLengthLabel()
{
    m_lengthLabel->setText(m_game->length().toString("h:mm:ss"));
}

void StatisticsGeneralPage::updateDealerLabel()
{
    if(m_game->rounds().last()->state() == Round::Finished)
        m_dealerLabel->setText("-");
    else
        m_dealerLabel->setText(m_game->rounds().last()->dealer()->name());
}

void StatisticsGeneralPage::updateNumberOfRoundsLabel()
{
    m_numberOfRoundsLabel->setText(QString::number(m_game->rounds().size()-1));
}

void StatisticsGeneralPage::updateReVsContraLabel()
{
}

void StatisticsGeneralPage::updateHochzeitenLabel()
{
}

void StatisticsGeneralPage::updateSoliLabel()
{
}

void StatisticsGeneralPage::updatePflichsoliLabel()
{
}

void StatisticsGeneralPage::updateTrumpfabgabenLabel()
{
}

void StatisticsGeneralPage::updateSchmeissereienLabel()
{
}

void StatisticsGeneralPage::updateSchweinereienLabel()
{
}

QLabel *StatisticsGeneralPage::addLabel(const QString &title, const QString &text)
{
    layout()->removeWidget(m_spacer);
    QFont f1("Helvetica",15, QFont::Normal, true);
    LBGui::Label *titleLabel = new LBGui::Label(title, this);
    titleLabel->setForegroundColor(QColor(200,200,200));
    titleLabel->setDropshadowColor(QColor(0,0,0));
    titleLabel->setAlignment(Qt::AlignBottom);
    titleLabel->setFont(f1);
    layout()->addWidget(titleLabel);

    QFont f2("Helvetica",30, QFont::Bold);
    LBGui::Label *textLabel = new LBGui::Label(text, this);
    textLabel->setForegroundColor(QColor(250,250,250));
    textLabel->setDropshadowColor(QColor(67,67,67));
    textLabel->setAlignment(Qt::AlignTop);
    textLabel->setFont(f2);
    layout()->addWidget(textLabel);
    layout()->addWidget(m_spacer);
    return textLabel;
}

} // namespace DokoLiveGameWindowNS

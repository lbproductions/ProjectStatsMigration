#include "pointstableitem.h"

#include <model/doppelkopfround.h>
#include <model/player.h>

namespace DokoLiveGameWindowNS {

PointsTableItem::PointsTableItem(DoppelkopfRound *round) :
    QTableWidgetItem(),
    m_doppelkopfRound(round)
{
}

PointsTablePlayerItem::PointsTablePlayerItem(Player *player, DoppelkopfRound *round) :
    PointsTableItem(round),
    m_player(player)
{
    if(m_doppelkopfRound->currentPlayingPlayers().contains(const_cast<Player*>(player)))
        setFlags(flags() & ~Qt::ItemIsSelectable);
    else
        setFlags(flags() & ~Qt::ItemIsSelectable & ~Qt::ItemIsEditable);

    setTextAlignment(Qt::AlignCenter);

    connect(round, SIGNAL(pointsChanged(const Player*,int)), this, SLOT(onPointsChanged(const Player*,int)));

    onPointsChanged(m_player, round->points(m_player));
}

void PointsTablePlayerItem::onPointsChanged(const Player* player, int points)
{
    if(player != m_player || !m_doppelkopfRound->currentPlayingPlayers().contains(const_cast<Player*>(player)))
        return;

    QString text = QString::number(points);
    if(m_doppelkopfRound->dokoSoloPlayer()) {
        if (m_doppelkopfRound->dokoSoloPlayer() == m_player) {
            text += " (S";
            if(m_doppelkopfRound->hochzeitPlayer() == m_player) {
                text += ",H)";
            }
            else if(m_doppelkopfRound->trumpfabgabePlayer() == m_player) {
                text += ",T)";
            }
            else {
                text += ")";
            }
            setText(text);
        }
        else {
            setText(text + " (C)");
        }
    }
    else {
        if (m_doppelkopfRound->isRe(m_player)) {
            text += " (R";
            if(m_doppelkopfRound->hochzeitPlayer() == m_player) {
                text += ",H)";
            }
            else if(m_doppelkopfRound->trumpfabgabePlayer() == m_player) {
                text += ",T)";
            }
            else {
                text += ")";
            }
            setText(text);
        }
        else {
            setText(text + " (C)");
        }
    }

    if (points < -9) {
        setBackgroundColor(QColor(255,0,0));
    }
    else if (points < -6) {
        setBackgroundColor(QColor(220,0,0));
    }
    else if (points < -3) {
        setBackgroundColor(QColor(188,0,0));
    }
    else if (points < 0) {
        setBackgroundColor(QColor(148,0,0));
    }
    else if (points > 9) {
        setBackgroundColor(QColor(24,255,0));
    }
    else if (points > 6) {
        setBackgroundColor(QColor(19,205,0));
    }
    else if (points > 3) {
        setBackgroundColor(QColor(13,141,0));
    }
    else if (points > 0) {
        setBackgroundColor(QColor(10,104,0));
    }
    else {
        setBackgroundColor("lightgray");
    }
}

int PointsTablePlayerItem::points() const
{
    return m_doppelkopfRound->points(m_player);
}

void PointsTablePlayerItem::setPoints(int points)
{
    if(m_doppelkopfRound->isContra(m_player))
        points = -points;

    foreach(Player* player, m_doppelkopfRound->currentPlayingPlayers())
    {
        if(m_doppelkopfRound->isRe(player)) {
            if(m_doppelkopfRound->dokoSoloPlayer() == player)
                m_doppelkopfRound->setPoints(player, 3*points);
            else
                m_doppelkopfRound->setPoints(player, points);
        }
        else {
            m_doppelkopfRound->setPoints(player, -points);
        }
    }
}

PointsTableTotalItem::PointsTableTotalItem(DoppelkopfRound *round) :
    PointsTableItem(round)
{
    setFlags(flags() & ~Qt::ItemIsSelectable);
    setTextAlignment(Qt::AlignCenter);

    connect(round, SIGNAL(roundPointsChanged()), this, SLOT(onPointsChanged()));
    onPointsChanged();
}

void PointsTableTotalItem::onPointsChanged()
{
    QString text = QString::number(m_doppelkopfRound->roundPoints());
    if(m_doppelkopfRound->roundPoints() > 0)
        text.prepend('+');
    setText(text);
}

int PointsTableTotalItem::points() const
{
    return text().toInt();
}

void PointsTableTotalItem::setPoints(int points)
{
    foreach(Player* player, m_doppelkopfRound->currentPlayingPlayers())
    {
        if(m_doppelkopfRound->isRe(player)) {
            if(m_doppelkopfRound->dokoSoloPlayer() == player)
                m_doppelkopfRound->setPoints(player, 3*points);
            else
                m_doppelkopfRound->setPoints(player, points);
        }
        else {
            m_doppelkopfRound->setPoints(player, -points);
        }
    }
}

}

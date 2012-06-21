#include "livegameplayerpointsgraph.h"

#include "livegamecoordinatesystem.h"
#include "graphpoint.h"

#include <model/player.h>
#include <model/livegame.h>
#include <model/round.h>

#include <QDebug>

using namespace Gui::Graphs::Items;

LiveGamePlayerPointsGraph::LiveGamePlayerPointsGraph(Player *player, LiveGame *liveGame, LiveGameCoordinateSystem *coordinateSystem) :
    Graph(coordinateSystem),
    m_player(player),
    m_liveGame(liveGame),
    m_totalPoints(0)
{
    connect(liveGame, SIGNAL(roundsRoundAdded(Round*)), this, SLOT(addRound(Round*)));
}

void LiveGamePlayerPointsGraph::setupGraph()
{
    m_pen.setColor(m_player->color());
    if(m_player->color() == QColor() || m_player->color() == QColor(0,0,0))
    {
        m_pen.setColor(QColor(255,255,255));
    }
    addPoint(QPoint(0,0));
    readPlayerPoints();
}

void LiveGamePlayerPointsGraph::readPlayerPoints()
{
    foreach(Round *r, m_liveGame->rounds()) {
        addRound(r);
    }
}

void LiveGamePlayerPointsGraph::addRound(Round *r)
{
    m_totalPoints += r->points(m_player);
    addPoint(QPoint(r->number()+1,m_totalPoints));
    m_points.last()->setToolTip("<h1>"+m_player->name()+"</h1>"+
                                 "<span style=\"font-size: 18pt;\">"+tr("Round")+" "+QString::number(r->number()+1)+"<br></span>"
                                 "<span style=\"font-size: 22pt;\">"
                                 "<b>"+tr("Points")+":</b> "+QString::number(r->points(m_player))+"<br>"+
                                 "<b>"+tr("Total")+":</b> "+QString::number(m_totalPoints)+
                                 "</span>");
}

Player* LiveGamePlayerPointsGraph::player()
{
    return m_player;
}

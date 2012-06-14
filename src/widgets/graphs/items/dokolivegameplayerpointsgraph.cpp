#include "dokolivegameplayerpointsgraph.h"

#include "livegamecoordinatesystem.h"
#include "dokographpoint.h"

#include <model/doppelkopflivegame.h>
#include <model/doppelkopfround.h>

#include <QDebug>
#include <QGraphicsScene>

using namespace Gui::Graphs::Items;

DokoLiveGamePlayerPointsGraph::DokoLiveGamePlayerPointsGraph(Player *player, DoppelkopfLiveGame *liveGame, LiveGameCoordinateSystem *coordinateSystem):
    LiveGamePlayerPointsGraph(player,liveGame,coordinateSystem)
{
}

void DokoLiveGamePlayerPointsGraph::addPoint(const QPoint &point)
{
    Graph::addPoint(point);
}

void DokoLiveGamePlayerPointsGraph::update()
{
    m_totalPoints = 0;
    m_xMax=0;
    m_yMax=0;
    m_xMin=0;
    m_yMin=0;
    int i = 0;

    foreach(GraphPoint* gpoint, m_points)
    {
        if(i == 0)
        {
            i = 1;
            continue;
        }
        DokoGraphPoint* point = static_cast<DokoGraphPoint*>(gpoint);
        DoppelkopfRound* round = point->round();
        if(round) {
            m_totalPoints += round->points(m_player);
            QPoint p = point->point();
            p.setY(m_totalPoints);
            point->setPoint(p);
            updateDimensions(p);
            emit pointAdded(p);
        }
    }

    m_coordinateSystem->updateDimensions();

    this->scene()->invalidate();
}

bool xCoordinateLessThan1(GraphPoint *p1, GraphPoint *p2)
{
    return p1->point().x() < p2->point().x();
}

void DokoLiveGamePlayerPointsGraph::addPoint(const QPoint &point, DoppelkopfRound *r)
{
    DokoGraphPoint *graphPoint = new DokoGraphPoint(point,this,r);
    m_points.append(graphPoint);

    qSort(m_points.begin(),m_points.end(),xCoordinateLessThan1);

    updateDimensions(point);
    emit pointAdded(point);
}

void DokoLiveGamePlayerPointsGraph::addRound(Round *r)
{
    DoppelkopfRound* dokoRound = static_cast<DoppelkopfRound*>(r);
    connect(dokoRound, SIGNAL(pointsChanged(const Player*,int)), this ,SLOT(update()));
    m_totalPoints += r->points(m_player);
    addPoint(QPoint(r->number()+1,m_totalPoints),dokoRound);
}

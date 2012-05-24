#ifndef DOKOGRAPHPOINT_H
#define DOKOGRAPHPOINT_H

#include "graphpoint.h"

class Player;
class DoppelkopfRound;

namespace Gui
{

namespace Graphs
{

namespace Items
{

class DokoLiveGamePlayerPointsGraph;

class DokoGraphPoint : public GraphPoint
{
    Q_OBJECT
public:
    DokoGraphPoint(QPoint point, DokoLiveGamePlayerPointsGraph* graph, DoppelkopfRound* r);

    /*!
      Zeichnet den Punkt.
      */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    DoppelkopfRound* round() const;
private:

    DoppelkopfRound* m_dokoRound;
    Player* m_player;
};

}}}

#endif // DOKOGRAPHPOINT_H

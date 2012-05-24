#ifndef DOKOLIVEGAMEPLAYERPOINTSGRAPH_H
#define DOKOLIVEGAMEPLAYERPOINTSGRAPH_H

#include "livegameplayerpointsgraph.h"


class Player;
class DoppelkopfLiveGame;
class DoppelkopfRound;

namespace Gui
{

namespace Graphs
{

namespace Items
{

class LiveGameCoordinateSystem;

class DokoLiveGamePlayerPointsGraph : public LiveGamePlayerPointsGraph
{
    Q_OBJECT
public:
    DokoLiveGamePlayerPointsGraph(Player *player, DoppelkopfLiveGame *liveGame, LiveGameCoordinateSystem *coordinateSystem);

    void addPoint(const QPoint &point);
    void addPoint(const QPoint &point, DoppelkopfRound* r);

public slots:
    void update();

    void addRound(Round*);
};

}}}

#endif // DOKOLIVEGAMEPLAYERPOINTSGRAPH_H

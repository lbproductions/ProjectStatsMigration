#include "dokolivegamecoordinatesystem.h"

#include "dokolivegameplayerpointsgraph.h"

#include "../../../model/doppelkopflivegame.h"

using namespace Gui::Graphs::Items;

DokoLiveGameCoordinateSystem::DokoLiveGameCoordinateSystem(DoppelkopfLiveGame* dokogame):
    LiveGameCoordinateSystem(dokogame)
{
}

void DokoLiveGameCoordinateSystem::addGraphsForPlayers()
{
    foreach(Player *player, m_liveGame->players()) {
        DokoLiveGamePlayerPointsGraph* graph = new DokoLiveGamePlayerPointsGraph(player,static_cast<DoppelkopfLiveGame*>(m_liveGame),this);
        graph->setupGraph();
        addGraph(graph);
    }
}

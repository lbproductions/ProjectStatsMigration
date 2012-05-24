#ifndef DOKOLIVEGAMECOORDINATESYSTEM_H
#define DOKOLIVEGAMECOORDINATESYSTEM_H

#include "livegamecoordinatesystem.h"


class DoppelkopfLiveGame;

namespace Gui
{

namespace Graphs
{

namespace Items
{

class DokoLiveGameCoordinateSystem  : public LiveGameCoordinateSystem
{
    Q_OBJECT
public:
    DokoLiveGameCoordinateSystem(DoppelkopfLiveGame *dokogame);

    void addGraphsForPlayers();
};

}}}

#endif // DOKOLIVEGAMECOORDINATESYSTEM_H

#ifndef DOKOLIVEGAMEGRAPHVIEW_H
#define DOKOLIVEGAMEGRAPHVIEW_H

#include "livegamegraphview.h"

namespace Gui
{
namespace Graphs
{

namespace Items
{
class DokoLiveGameCoordinateSystem;
}

class DokoLiveGameGraphView :public LiveGameGraphView
{
    Q_OBJECT
public:
    DokoLiveGameGraphView(QWidget *parent);

    void setLiveGame(LiveGame *liveGame);
};

}}

#endif // DOKOLIVEGAMEGRAPHVIEW_H

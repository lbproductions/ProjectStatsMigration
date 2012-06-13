#include "dokolivegamegraphview.h"

#include "items/dokolivegamecoordinatesystem.h"

#include <model/doppelkopflivegame.h>

DokoLiveGameGraphView::DokoLiveGameGraphView(QWidget *parent):
    LiveGameGraphView(parent)
{
}

void DokoLiveGameGraphView::setLiveGame(LiveGame *liveGame)
{
    if(!m_liveGameCoordinateSystem.isNull()) {
        scene()->removeItem(m_liveGameCoordinateSystem);
        m_liveGameCoordinateSystem->deleteLater();
    }

    m_liveGameCoordinateSystem = new Gui::Graphs::Items::DokoLiveGameCoordinateSystem(static_cast<DoppelkopfLiveGame*>(liveGame));
    m_liveGameCoordinateSystem->setParent(this);
    m_liveGameCoordinateSystem->setupSystem();
    connect(m_liveGameCoordinateSystem,SIGNAL(dimensionsChanged(QRectF)),this,SLOT(on_coordinateSystem_dimensionsChanged(QRectF)));


    scene()->addItem(m_liveGameCoordinateSystem);
    scene()->update();
}

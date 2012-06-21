#include "statisticssidebar.h"

#include "statisticsgeneralpage.h"

namespace DokoLiveGameWindowNS {

StatisticsSidebar::StatisticsSidebar(QWidget *parent) :
    LiveGameSidebar(parent)
{
    m_generalPage = new StatisticsGeneralPage(this);
    addPage(tr("General"), m_generalPage);
}

void StatisticsSidebar::setDoppelkopfLiveGame(DoppelkopfLiveGame *game)
{
    m_generalPage->setDoppelkopfLiveGame(game);
}

} // namespace DokoLiveGameWindowNS

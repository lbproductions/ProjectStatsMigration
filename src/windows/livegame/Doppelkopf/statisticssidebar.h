#ifndef DOKOLIVEGAMEWINDOWNS_STATISTICSSIDEBAR_H
#define DOKOLIVEGAMEWINDOWNS_STATISTICSSIDEBAR_H

#include "../livegamesidebar.h"

class DoppelkopfLiveGame;
class QLabel;

namespace DokoLiveGameWindowNS {

class StatisticsGeneralPage;

class StatisticsSidebar : public LiveGameWindowNS::LiveGameSidebar
{
public:
    StatisticsSidebar(QWidget *parent = 0);

    void setDoppelkopfLiveGame(DoppelkopfLiveGame *game);

private:
    QLabel *addLabel(const QString &title, const QString &text);

    StatisticsGeneralPage *m_generalPage;
};

} // namespace DokoLiveGameWindowNS

#endif // DOKOLIVEGAMEWINDOWNS_STATISTICSSIDEBAR_H

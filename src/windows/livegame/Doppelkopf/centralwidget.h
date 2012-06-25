#ifndef DOKOLIVEGAMEWINDOWNS_CENTRALWIDGET_H
#define DOKOLIVEGAMEWINDOWNS_CENTRALWIDGET_H

#include <QWidget>

class DoppelkopfLiveGame;
class DokoLiveGameWindow;
class DokoLiveGameGraphView;

namespace LiveGameWindowNS {
class DrinksSidebarPage;
}

namespace DokoLiveGameWindowNS {

class StatisticsSidebar;
class PointsTable;
class TotalPointsTable;

class CentralWidget : public QWidget
{

public:
    explicit CentralWidget(DokoLiveGameWindow *parent = 0);
    ~CentralWidget();

    void setDoppelkopfLiveGame(DoppelkopfLiveGame *doppelkopfLiveGame);

    StatisticsSidebar *statisticsSidebar() const;

private:
    DoppelkopfLiveGame *m_doppelkopfLiveGame;

    DokoLiveGameGraphView *m_graphView;
    PointsTable *m_pointsTable;
    TotalPointsTable *m_totalPointsTable;
    LiveGameWindowNS::DrinksSidebarPage *m_drinksPage;
    StatisticsSidebar *m_rightSidebar;
};

}

#endif // DOKOLIVEGAMEWINDOWNS_CENTRALWIDGET_H

#ifndef DOKOLIVEGAMEWINDOWNS_STATISTICSGENERALPAGE_H
#define DOKOLIVEGAMEWINDOWNS_STATISTICSGENERALPAGE_H

#include "../sidebarpage.h"

class LiveGameSidebar;
class QLabel;
class DoppelkopfLiveGame;

namespace DokoLiveGameWindowNS {

class StatisticsSidebar;

class StatisticsGeneralPage : public LiveGameWindowNS::SidebarPage
{
    Q_OBJECT
public:
    StatisticsGeneralPage(StatisticsSidebar *parent = 0);

    void setDoppelkopfLiveGame(DoppelkopfLiveGame *game);

private slots:
    void updateCurrentTimeLabel();
    void updateLengthLabel();
    void updateDealerLabel();
    void updateNumberOfRoundsLabel();
    void updateReVsContraLabel();
    void updateHochzeitenLabel();
    void updateSoliLabel();
    void updatePflichsoliLabel();
    void updateTrumpfabgabenLabel();
    void updateSchmeissereienLabel();
    void updateSchweinereienLabel();

private:
    QLabel *addLabel(const QString &title, const QString &text);
    void addSeparator();


    QLayout *m_layout;

    DoppelkopfLiveGame *m_game;

    QWidget *m_spacer;

    QLabel *m_currentTimeLabel;
    QLabel *m_lengthLabel;
    QLabel *m_dealerLabel;
    QLabel *m_numberOfRoundsLabel;
    QLabel *m_reVsContraLabel;
    QLabel *m_hochzeitenLabel;
    QLabel *m_soliLabel;
    QLabel *m_pflichsoliLabel;
    QLabel *m_trumpfabgabenLabel;
    QLabel *m_schmeissereienLabel;
    QLabel *m_schweinereienLabel;
};

} // namespace DokoLiveGameWindowNS

#endif // DOKOLIVEGAMEWINDOWNS_STATISTICSGENERALPAGE_H

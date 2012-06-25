#ifndef DOKOLIVEGAMEWINDOW_H
#define DOKOLIVEGAMEWINDOW_H

#include "../livegamewindow.h"

class DoppelkopfLiveGame;

namespace DokoLiveGameWindowNS {
class CentralWidget;
}

class DokoLiveGameWindow : public LiveGameWindow
{
    Q_OBJECT
public:
    explicit DokoLiveGameWindow(QWidget *parent = 0);

    void setDoppelkopfLiveGame(DoppelkopfLiveGame *doppelkopfLiveGame);

    void openNewInstance();

private slots:
    void reflectState(LiveGame::State state);

    void showNewSchmeissereiDialog();
    void showNewRoundDialog();
    void showEndGameDialog();

private:
    DoppelkopfLiveGame *m_doppelkopfLiveGame;
    QAction *m_actionShowSchmeissereiDialog;
    DokoLiveGameWindowNS::CentralWidget *m_centralWidget;

    void setupToolBar();
};

#endif // DOKOLIVEGAMEWINDOW_H

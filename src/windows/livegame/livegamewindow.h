#ifndef LIVEGAMEWINDOW_H
#define LIVEGAMEWINDOW_H

#include <QMainWindow>


class LiveGame;

class LiveGameWindow : public QMainWindow
{
    Q_OBJECT
public:
    LiveGameWindow();
    ~LiveGameWindow();

    void setGame(LiveGame *game);

protected:
    LiveGame *m_livegame;
//    LiveGameWidget *m_liveGameDetailsWidget;

    QToolBar *m_toolbar;

    QAction* m_actionFullScreen;
    QAction* m_actionPause;
    QAction* m_actionNewRound;
    QAction* m_actionCloseGame;
    QAction* m_actionAddDrink;
    QAction* m_actionSettings;

    /**
    * Erstellt eine neue Toolbar mit den zugehörigen Actions für das LiveGame.
    */
    void setupToolBar();

protected slots:
    virtual void reflectState();

    /**
    * Wird von der Action m_actionFullScreen aufgerufen. Wechelt je nach Zustand von state zwischen Fullscreen-Mode und Normal-Mode.
    */
    void setFullScreen(bool state);

    /**
    * Wird von der Action m_actionPause aufgerufen. Wechselt je nach Zustand von state zwischen Pausieren und Fortsetzen des LiveGames.
    */
    void pauseLiveGame(bool pause);

    /**
    * Wird von der Action m_actionCloseGame aufgerufen. Öffnet das EndLiveGameWidget und verknüpft dessen Signal liveGameClosed() mit dem Slot onLiveGameClosed.
    */
    virtual void showEndGameDialog();

    /**
    * Wird von der Action m_actionNewRound aufgerufen. Wechselt je nach Zustand von state zwischen Darstellen und Löschen des NewDokoRoundWidgets.
    */
    virtual void showNewRoundDialog();

    void showAddDrinkDialog();
};

#endif // LIVEGAMEWINDOW_H

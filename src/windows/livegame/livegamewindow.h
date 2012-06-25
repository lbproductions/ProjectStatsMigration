#ifndef LIVEGAMEWINDOW_H
#define LIVEGAMEWINDOW_H

#include <QMainWindow>

#include <model/livegame.h>

class LiveGameWindowCentralWidget;

class LiveGameWindow : public QMainWindow
{
    Q_OBJECT
public:
    LiveGameWindow(QWidget *parent = 0);
    ~LiveGameWindow();

    void setLiveGame(LiveGame *liveGame);

protected slots:
    virtual void showEndGameDialog();
    virtual void showNewRoundDialog();
    virtual void reflectState(LiveGame::State state);

    virtual void openNewInstance();

protected:
    enum ToolBarPosition {
        LeftToolBarPosition,
        MiddleToolBarPosition,
        RightToolBarPosition
    };

    void addToolBarAction(QAction *action, ToolBarPosition position);

private slots:
    void setFullScreen(bool fullScreen);
    void pauseLiveGame(bool pause);

    void showAddDrinkDialog();

private:
    void setupToolBar();

    LiveGame *m_liveGame;

    QToolBar *m_toolBar;

    QAction* m_actionFullScreen;
    QAction* m_actionPause;
    QAction* m_actionShowNewRoundDialog;
    QAction* m_actionShowEndGameDialog;
    QAction* m_actionShowAddDrinkDialog;
};

#endif // LIVEGAMEWINDOW_H

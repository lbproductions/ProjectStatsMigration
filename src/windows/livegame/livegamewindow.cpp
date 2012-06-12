#include "livegamewindow.h"

#include "../../model/livegame.h"

#include <QAction>
#include <QToolBar>
#include <QLabel>
#include <QDebug>

LiveGameWindow::LiveGameWindow() :
    QMainWindow(),
    m_livegame(0)
{
    setupToolBar();

    setAttribute(Qt::WA_DeleteOnClose);
}

LiveGameWindow::~LiveGameWindow()
{
    if(m_livegame && m_livegame->state() == LiveGame::Running)
        m_livegame->setState(LiveGame::Paused);
}

void LiveGameWindow::setGame(LiveGame *game)
{
    if(game == m_livegame)
        return;

    m_livegame = game;
    connect(m_livegame, SIGNAL(stateChanged(State)), this, SLOT(reflectState()));
    reflectState();
}

void LiveGameWindow::setupToolBar()
{
    m_toolbar = new QToolBar(tr("Live Game"));
    m_toolbar->setIconSize(QSize(50,44));
    m_toolbar->setMovable(false);
    m_toolbar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    addToolBar(m_toolbar);

    m_actionPause = new QAction(QIcon(":/graphics/icons/livegame/pause"),tr("Pause"),m_toolbar);
    m_actionPause->setCheckable(true);
    connect(m_actionPause,SIGNAL(triggered(bool)),this,SLOT(pauseLiveGame(bool)));
    m_toolbar->addAction(m_actionPause);

    m_actionCloseGame = new QAction(QIcon(":/graphics/icons/livegame/closegame"),tr("End Game"),m_toolbar);
    connect(m_actionCloseGame,SIGNAL(triggered()),this,SLOT(showEndGameDialog()));
    m_toolbar->addAction(m_actionCloseGame);

    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_toolbar->addWidget(spacer);

    m_actionAddDrink = new QAction(QIcon(":/graphics/icons/livegame/bierbutton"),tr("Add Drink"),m_toolbar);
    connect(m_actionAddDrink,SIGNAL(triggered()),this,SLOT(showAddDrinkDialog()));
    m_toolbar->addAction(m_actionAddDrink);

    m_actionNewRound = new QAction(QIcon(":/graphics/icons/livegame/newround"),tr("New Round"),m_toolbar);
    connect(m_actionNewRound,SIGNAL(triggered()),this,SLOT(showNewRoundDialog()));
    m_toolbar->addAction(m_actionNewRound);

    QIcon iconFullscreen(":/graphics/icons/livegame/fullscreen");
    m_actionFullScreen = new QAction(iconFullscreen,tr("Fullscreen"),m_toolbar);
    m_actionFullScreen->setCheckable(true);
    connect(m_actionFullScreen, SIGNAL(triggered(bool)), this, SLOT(setFullScreen(bool)));
    m_toolbar->addAction(m_actionFullScreen);

    setUnifiedTitleAndToolBarOnMac(true);
}


void LiveGameWindow::setFullScreen(bool state)
{
    if (state)
    {
#if true //!defined Q_OS_MAC || MAC_OS_X_VERSION_MAX_ALLOWED < MAC_OS_X_VERSION_10_7
        this->showFullScreen();
#else
        //setUnifiedTitleAndToolBarOnMac(false);
        toggleFullscreen(this);
#endif
        m_actionFullScreen->setIcon(QIcon(":/graphics/icons/mac/livegame/normal"));
        m_actionFullScreen->setText(tr("Exit Fullscreen"));
        m_toolbar->setStyleSheet("QWidget { background-image: url(:/graphics/styles/mac/toolbar/fullscreen/toolbar_background_fullscreen); border: 0px solid transparent; border-bottom: 1px solid gray;color: white;}");
    }
    else
    {
        this->setMinimumSize(100,100);
#ifndef true // Q_OS_MAC
        this->showNormal();
#else
        toggleFullscreen(this);
        //setUnifiedTitleAndToolBarOnMac(true);
#endif
        m_actionFullScreen->setIcon(QIcon(":/graphics/icons/mac/livegame/fullscreen"));
        m_actionFullScreen->setText(tr("Fullscreen"));
        m_toolbar->setStyleSheet("");
    }
}

void LiveGameWindow::pauseLiveGame(bool pause)
{
    if(pause)
        m_livegame->setState(LiveGame::Paused);
    else
        m_livegame->setState(LiveGame::Running);
}

void LiveGameWindow::showEndGameDialog()
{
    //TODO: engamewidget zeigen
//    Gui::Details::LiveGameDetails::EndLiveGameWidget endGameWidget(m_livegame,this);
//    endGameWidget.exec();
}

void LiveGameWindow::reflectState()
{
    m_actionPause->setEnabled(true);
    m_actionNewRound->setEnabled(true);
    m_actionCloseGame->setEnabled(true);
    m_actionAddDrink->setEnabled(true);
    m_actionPause->setEnabled(true);
    m_actionNewRound->setEnabled(true);

    if(!m_livegame)
        return;

    LiveGame::State state = m_livegame->state();
    switch(state)
    {
    case LiveGame::Paused:
        m_actionPause->setIcon(QIcon(":/graphics/icons/livegame/play"));
        m_actionPause->setText(tr("Play"));
        m_actionPause->setChecked(true);
        m_actionNewRound->setEnabled(false);
        break;

    case LiveGame::Finished:
        m_actionPause->setEnabled(false);
        m_actionNewRound->setEnabled(false);
        m_actionCloseGame->setEnabled(false);
        m_actionAddDrink->setEnabled(false);
        m_actionPause->setEnabled(false);
        m_actionNewRound->setEnabled(false);
        break;

    case LiveGame::Running:
        m_actionPause->setIcon(QIcon(":/graphics/icons/livegame/pause"));
        m_actionPause->setText(tr("Pause"));
        break;

    default:
        break;
    }
}

void LiveGameWindow::showAddDrinkDialog()
{
    //TODO: show addrink dialog
//    LiveGameDetails::AddDrinkWidget addDrinkDialog(this);
//    addDrinkDialog.exec();
}

void LiveGameWindow::showNewRoundDialog()
{
}

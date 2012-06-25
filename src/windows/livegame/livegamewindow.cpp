#include "livegamewindow.h"

#include "adddrinkwidget.h"

#include <model/livegame.h>
#include <model/storage.h>

#include <QAction>
#include <QToolBar>
#include <QLabel>
#include <QDebug>
#include <QFile>

LiveGameWindow::LiveGameWindow(QWidget *parent) :
    QMainWindow(parent),
    m_liveGame(0)
{
    setupToolBar();

    setAttribute(Qt::WA_DeleteOnClose);

    setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint);
}

LiveGameWindow::~LiveGameWindow()
{
    if(m_liveGame && m_liveGame->state() == LiveGame::Running)
        m_liveGame->setState(LiveGame::Paused);
}

void LiveGameWindow::setLiveGame(LiveGame *liveGame)
{
    if(liveGame == m_liveGame)
        return;

    m_liveGame = liveGame;
    connect(m_liveGame, SIGNAL(stateChanged(LiveGame::State)), this, SLOT(reflectState(LiveGame::State)));
    reflectState(m_liveGame->state());
}

void LiveGameWindow::setupToolBar()
{
    m_toolBar = new QToolBar(tr("Live Game"));
    m_toolBar->setIconSize(QSize(36,36));
    m_toolBar->setFixedHeight(55);
    m_toolBar->setMovable(false);
    m_toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    addToolBar(Qt::BottomToolBarArea, m_toolBar);

    m_actionPause = new QAction(QIcon(":/graphics/icons/livegame/pause"),tr("Pause"),m_toolBar);
    m_actionPause->setCheckable(true);
    connect(m_actionPause,SIGNAL(triggered(bool)),this,SLOT(pauseLiveGame(bool)));
    m_toolBar->addAction(m_actionPause);

    m_actionShowEndGameDialog = new QAction(QIcon(":/graphics/icons/livegame/closegame"),tr("End Game"),m_toolBar);
    connect(m_actionShowEndGameDialog,SIGNAL(triggered()),this,SLOT(showEndGameDialog()));
    m_toolBar->addAction(m_actionShowEndGameDialog);

    QWidget* spacer = new QWidget(m_toolBar);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_toolBar->addWidget(spacer);

    m_actionShowNewRoundDialog = new QAction(QIcon(":/graphics/icons/livegame/newround"),tr("New Round"),m_toolBar);
    connect(m_actionShowNewRoundDialog,SIGNAL(triggered()),this,SLOT(showNewRoundDialog()));
    m_toolBar->addAction(m_actionShowNewRoundDialog);

    m_actionShowAddDrinkDialog = new QAction(QIcon(":/graphics/icons/livegame/bierbutton"),tr("Add Drink"),m_toolBar);
    connect(m_actionShowAddDrinkDialog,SIGNAL(triggered()),this,SLOT(showAddDrinkDialog()));
    m_toolBar->addAction(m_actionShowAddDrinkDialog);

    spacer = new QWidget(m_toolBar);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_toolBar->addWidget(spacer);

    QIcon iconFullscreen(":/graphics/icons/livegame/fullscreen");
    m_actionFullScreen = new QAction(iconFullscreen,tr("Fullscreen"),m_toolBar);
    m_actionFullScreen->setCheckable(true);
    connect(m_actionFullScreen, SIGNAL(triggered(bool)), this, SLOT(setFullScreen(bool)));
    m_toolBar->addAction(m_actionFullScreen);

    QFile stylesheet(QLatin1String(":/toolbar/black/stylesheet"));
    stylesheet.open(QFile::ReadOnly);
    m_toolBar->setStyleSheet(stylesheet.readAll());
    stylesheet.close();
}


void LiveGameWindow::setFullScreen(bool fullScreen)
{
    if (fullScreen) {
        showFullScreen();
        setAcceptDrops(true);

        m_actionFullScreen->setIcon(QIcon(":/graphics/icons/livegame/normalmode"));
        m_actionFullScreen->setText(tr("Exit Fullscreen"));
    }
    else {
        showNormal();
        setAcceptDrops(true);

        m_actionFullScreen->setIcon(QIcon(":/graphics/icons/livegame/normalmode"));
        m_actionFullScreen->setText(tr("Exit Fullscreen"));
    }
}

void LiveGameWindow::pauseLiveGame(bool pause)
{
    if(pause)
        m_liveGame->setState(LiveGame::Paused);
    else
        m_liveGame->setState(LiveGame::Running);
}

void LiveGameWindow::showEndGameDialog()
{
    //TODO: engamewidget zeigen
//    Gui::Details::LiveGameDetails::EndLiveGameWidget endGameWidget(m_livegame,this);
//    endGameWidget.exec();
}

void LiveGameWindow::reflectState(LiveGame::State state)
{
    m_actionPause->setEnabled(true);
    m_actionShowNewRoundDialog->setEnabled(true);
    m_actionShowEndGameDialog->setEnabled(true);
    m_actionShowAddDrinkDialog->setEnabled(true);
    m_actionPause->setEnabled(true);
    m_actionShowNewRoundDialog->setEnabled(true);

    switch(state)
    {
    case LiveGame::Paused:
        m_actionPause->setIcon(QIcon(":/graphics/icons/livegame/play"));
        m_actionPause->setText(tr("Play"));
        m_actionPause->setChecked(true);
        m_actionShowNewRoundDialog->setEnabled(false);
        break;

    case LiveGame::Running:
        m_actionPause->setIcon(QIcon(":/graphics/icons/livegame/pause"));
        m_actionPause->setText(tr("Pause"));
        break;

    default:
    case LiveGame::Finished:
        m_actionPause->setEnabled(false);
        m_actionShowNewRoundDialog->setEnabled(false);
        m_actionShowEndGameDialog->setEnabled(false);
        m_actionShowAddDrinkDialog->setEnabled(false);
        m_actionPause->setEnabled(false);
        m_actionShowNewRoundDialog->setEnabled(false);
        break;
    }
}

void LiveGameWindow::showAddDrinkDialog()
{
}

void LiveGameWindow::showNewRoundDialog()
{
}

void LiveGameWindow::addToolBarAction(QAction *action, LiveGameWindow::ToolBarPosition position)
{
    switch(position) {
    case LeftToolBarPosition:
        m_toolBar->insertAction(m_actionShowEndGameDialog, action);
        break;
    case MiddleToolBarPosition:
        m_toolBar->insertAction(m_actionShowAddDrinkDialog, action);
        break;
    case RightToolBarPosition:
        m_toolBar->insertAction(m_actionFullScreen, action);
    }
}

#include "centralwidget.h"

#include "dokolivegamewindow.h"
#include "pointstable.h"
#include "totalpointstable.h"
#include "statisticssidebar.h"

#include "../livegamesidebar.h"
#include "../sidebarpage.h"
#include "../drinkssidebarpage.h"

#include <widgets/graphs/dokolivegamegraphview.h>
#include <model/doppelkopflivegame.h>

#include <LBGui/LBGui.h>

#include <QSplitter>

namespace DokoLiveGameWindowNS {

CentralWidget::CentralWidget(DokoLiveGameWindow *parent) :
    QWidget(parent),
    m_doppelkopfLiveGame(0)
{
    setAutoFillBackground(true);
    QPalette p = palette();
    p.setColor(QPalette::Window, QColor(45,45,45));
    setPalette(p);

    // Central
    QSplitter* splitterCentral = new QSplitter(Qt::Vertical,this);
    LBGui::GroupBox* groupBoxPointsTable = new LBGui::GroupBox(splitterCentral);
    LBGui::GroupBox* groupBoxTotalPointsTable = new LBGui::GroupBox(splitterCentral);
    LBGui::GroupBox* groupBoxGraph = new LBGui::GroupBox(splitterCentral);
    groupBoxPointsTable->setStyle(LBGui::GroupBox::IphotoDark);
    groupBoxTotalPointsTable->setStyle(LBGui::GroupBox::IphotoDark);
    groupBoxGraph->setStyle(LBGui::GroupBox::IphotoDark);

    splitterCentral->addWidget(groupBoxPointsTable);
    splitterCentral->addWidget(groupBoxTotalPointsTable);
    splitterCentral->addWidget(groupBoxGraph);

//    splitterCentral->setStretchFactor(0,1);
//    splitterCentral->setStretchFactor(1,0);
//    splitterCentral->setStretchFactor(2,2);

    QWidget* centralWidget = new QWidget(this);
    QLayout* centralLayout = new QVBoxLayout(this);
    centralLayout->setSpacing(0);
    centralLayout->setContentsMargins(12,12,12,12);
    centralLayout->addWidget(splitterCentral);
    centralWidget->setLayout(centralLayout);

    m_graphView = new DokoLiveGameGraphView(groupBoxGraph);
    m_graphView->setStyleSheet("QWidget{background: transparent; color:white; border: none;}");
    groupBoxGraph->layout()->addWidget(m_graphView);

    m_pointsTable = new PointsTable(groupBoxPointsTable);
    groupBoxPointsTable->layout()->addWidget(m_pointsTable);

    m_totalPointsTable = new TotalPointsTable(groupBoxTotalPointsTable);
    groupBoxTotalPointsTable->layout()->addWidget(m_totalPointsTable);
    groupBoxTotalPointsTable->layout()->setContentsMargins(5,5,0,0);
    groupBoxTotalPointsTable->setFixedHeight(40);

    // Left
//    LBGui::Splitter* leftSplitter = new LBGui::Splitter(Qt::Horizontal);
//    leftSplitter->setStyle(LBGui::Splitter::MacOSFullscreenStyle);
//    leftSplitter->setDirection(LBGui::Splitter::LeftToRight);

//    LiveGameWindowNS::LiveGameSidebar *leftSideBar = new LiveGameWindowNS::LiveGameSidebar(leftSplitter);
//    m_drinksPage = new LiveGameWindowNS::DrinksSidebarPage(leftSideBar);

//    leftSideBar->addPage(tr("Drinks"), m_drinksPage);
//    //leftSideBar->addPage(tr("Statistics"), new LiveGameWindowNS::SidebarPage(leftSideBar));

//    leftSplitter->addWidget(leftSideBar);
//    leftSplitter->addWidget(centralWidget);
//    leftSplitter->setStretchFactor(0,0);
//    leftSplitter->setStretchFactor(1,1);



    LBGui::Splitter* rightSplitter = new LBGui::Splitter(Qt::Horizontal);
    rightSplitter->setStyle(LBGui::Splitter::MacOSFullscreenStyle);
    rightSplitter->setDirection(LBGui::Splitter::RightToLeft);

    m_rightSidebar = new StatisticsSidebar(rightSplitter);

    m_drinksPage = new LiveGameWindowNS::DrinksSidebarPage(m_rightSidebar);

    m_rightSidebar->addPage(tr("Drinks"), m_drinksPage);
    m_rightSidebar->addPage(tr("Comment"), new LiveGameWindowNS::DrinksSidebarPage(m_rightSidebar));

    rightSplitter->addWidget(centralWidget);
    rightSplitter->addWidget(m_rightSidebar);

    rightSplitter->setStretchFactor(0,1);
    rightSplitter->setStretchFactor(1,0);

    QHBoxLayout *l = new QHBoxLayout(this);
    l->setContentsMargins(0,0,0,0);
    l->setSpacing(0);
    l->addWidget(rightSplitter);
    setLayout(l);

    m_rightSidebar->setCurrentPage(0);
}

CentralWidget::~CentralWidget()
{
}

void CentralWidget::setDoppelkopfLiveGame(DoppelkopfLiveGame *doppelkopfLiveGame)
{
    if(doppelkopfLiveGame == m_doppelkopfLiveGame)
        return;

    m_doppelkopfLiveGame = doppelkopfLiveGame;
    m_graphView->setLiveGame(m_doppelkopfLiveGame);
    m_pointsTable->setDoppelkopfLiveGame(m_doppelkopfLiveGame);
    m_totalPointsTable->setDoppelkopfLiveGame(m_doppelkopfLiveGame);
    m_rightSidebar->setDoppelkopfLiveGame(m_doppelkopfLiveGame);

    m_drinksPage->setLiveGame(m_doppelkopfLiveGame);
    foreach(Player *p, doppelkopfLiveGame->players()) {
        m_drinksPage->addPlayer(p);
    }
}

StatisticsSidebar *CentralWidget::statisticsSidebar() const
{
    return m_rightSidebar;
}

}

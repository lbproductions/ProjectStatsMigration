#include "centralwidget.h"

#include "dokolivegamewindow.h"
#include "pointstable.h"

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
    setBackgroundRole(QPalette::Background);
    QPalette p(palette());
    p.setColor(QPalette::Background, QColor(55,55,55));
    setPalette(p);

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

    splitterCentral->setStretchFactor(0,1);
    splitterCentral->setStretchFactor(1,0);
    splitterCentral->setStretchFactor(2,2);

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

    QHBoxLayout *l = new QHBoxLayout(this);
    l->addWidget(centralWidget);
    setLayout(l);

//    Gui::Misc::Splitter* leftSplitter = new Gui::Misc::Splitter(Qt::Horizontal);
//    leftSplitter->setFullscreen(true);
//    leftSplitter->setLeftToRight(true);
//    leftSplitter->addWidget(new BeerWidget(m_livegame,leftSplitter));
//    leftSplitter->addWidget(centralWidget);
//    leftSplitter->setStretchFactor(0,0);
//    leftSplitter->setStretchFactor(1,1);

//    Gui::Misc::Splitter* rightSplitter = new Gui::Misc::Splitter(Qt::Horizontal);
//    rightSplitter->setFullscreen(true);
//    rightSplitter->addWidget(leftSplitter);
//    rightSplitter->addWidget(m_infoBox);
//    rightSplitter->setStretchFactor(0,1);
//    rightSplitter->setStretchFactor(1,0);

//    QLayout* l = new QVBoxLayout(this);
//    l->setSpacing(0);
//    l->setContentsMargins(0,0,0,0);
//    l->addWidget(rightSplitter);
//    setLayout(l);

//    m_playerTotalPointsTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    m_playerTotalPointsTable->setGridStyle(Qt::NoPen);
//    m_playerTotalPointsTable->horizontalHeader()->hide();
//    m_playerTotalPointsTable->verticalHeader()->hide();
//    int i = 0;
//    for (;i<m_playerTotalPointsTable->columnCount();i++)
//    {
//         Gui::Misc::ConnectableTableWidgetItem* item = new Gui::Misc::ConnectableTableWidgetItem();
//         item->setTextAlignment(Qt::AlignCenter);
//         item->setFont(QFont("Lucia Grande",35,QFont::Bold,false));
//         item->setFlags(item->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);

//         if(i < m_livegame->playersSortedByPosition->value().size())
//         {
//             m_livegame->points->mappingFutureWatcher(m_livegame->playersSortedByPosition->value().at(i))->connectTo(item);
//         }
//         else
//         {
//             m_livegame->totalPoints->futureWatcher()->connectTo(item);
//         }
//         m_playerTotalPointsTable->setItem(0,i,item);
//    }

//    m_playerTotalPointsTable->setRowHeight(0,35);
//    m_playerTotalPointsTable->setMaximumHeight(m_playerTotalPointsTable->rowHeight(0));

//    m_playerTotalPointsTable->setStyleSheet("QWidget{margin: 0px; padding: 0px; background:transparent; color: white;}");
//    updateSizes();
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
}

}

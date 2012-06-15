#include "totalpointstable.h"

#include <model/doppelkopflivegame.h>
#include <model/player.h>

#include <QHeaderView>

namespace DokoLiveGameWindowNS {

TotalPointsTable::TotalPointsTable(QWidget *parent) :
    QTableWidget(parent),
    m_doppelkopfLiveGame(0)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setGridStyle(Qt::NoPen);
    horizontalHeader()->hide();
    verticalHeader()->hide();
//    setFixedHeight(50);

    setStyleSheet("QWidget{margin: 0px; padding: 0px; background:transparent; color: white;}");
}

void TotalPointsTable::setDoppelkopfLiveGame(DoppelkopfLiveGame *doppelkopfLiveGame)
{
    if(doppelkopfLiveGame == m_doppelkopfLiveGame)
        return;

    m_doppelkopfLiveGame = doppelkopfLiveGame;
    connect(m_doppelkopfLiveGame->function(LiveGameProperties::PointsFunction), SIGNAL(changed()), this, SLOT(updateContents()));
    connect(m_doppelkopfLiveGame->attribute(LiveGameProperties::TotalPointsAttribute), SIGNAL(changed()), this, SLOT(updateContents()));

    insertRow(0);
    int column = 0;
    foreach(Player *player, doppelkopfLiveGame->players()) {
        insertColumn(column);
        setRowHeight(column,35);
        QTableWidgetItem *item = new QTableWidgetItem(QString::number(doppelkopfLiveGame->points(player)));
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item->setFont(QFont("Lucia Grande",35,QFont::Bold,false));
        item->setFlags(item->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);

        setItem(0,column++,item);
    }

    insertColumn(column);
    setRowHeight(column,35);
    QTableWidgetItem *item = new QTableWidgetItem(QString::number(doppelkopfLiveGame->totalPoints()));
    item->setTextAlignment(Qt::AlignCenter);
    item->setFont(QFont("Lucia Grande",35,QFont::Bold,false));
    item->setFlags(item->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);
    setItem(0,column++,item);

    insertColumn(column);
    setRowHeight(column,35);
    item = new QTableWidgetItem();
    item->setFlags(item->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);
    setItem(0,column++,item);
}

void TotalPointsTable::resizeEvent(QResizeEvent* event)
{
    Q_UNUSED(event)
    if(!m_doppelkopfLiveGame)
        return;

    double w = (width() / (0.5 + m_doppelkopfLiveGame->players().size()) );

    for (int i = 0;  i < columnCount()-2; i++) {
        setColumnWidth(i,w-3);
    }
    setColumnWidth(columnCount()-1, w / 8);
    setColumnWidth(columnCount()-1, w / 8);
    QTableWidget::resizeEvent(event);
}

void TotalPointsTable::updateContents()
{
    int column = 0;
    foreach(Player *player, m_doppelkopfLiveGame->players()) {
        item(0,column++)->setText(QString::number(m_doppelkopfLiveGame->points(player)));
    }

    item(0, column)->setText(QString::number(m_doppelkopfLiveGame->totalPoints()));
}

} // namespace DokoLiveGameWindowNS

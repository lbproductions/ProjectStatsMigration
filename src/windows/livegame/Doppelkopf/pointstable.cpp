#include "pointstable.h"

#include "pointstableitem.h"
#include "pointstabledelegate.h"

#include <model/doppelkopflivegame.h>
#include <model/doppelkopfround.h>
#include <model/player.h>

#include <QFile>
#include <QDebug>

namespace DokoLiveGameWindowNS {

PointsTable::PointsTable(QWidget *parent):
    QTableWidget(parent),
    m_doppelkopfLiveGame(0)
{
    QFile stylesheet(":/stylesheets/pointstable");
    stylesheet.open(QFile::ReadOnly);
    QString style(stylesheet.readAll());
    stylesheet.close();

    QFile stylesheet2(":/scrollbar/iphoto_dark/stylesheet");
    stylesheet2.open(QFile::ReadOnly);
    style += stylesheet2.readAll();
    stylesheet2.close();

    setStyleSheet(style);

    setGridStyle(Qt::NoPen);

    setItemDelegate(new PointsTableDelegate(this));

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void PointsTable::setDoppelkopfLiveGame(DoppelkopfLiveGame *doppelkopfLiveGame)
{
    if(doppelkopfLiveGame == m_doppelkopfLiveGame)
        return;

    m_doppelkopfLiveGame = doppelkopfLiveGame;
    connect(m_doppelkopfLiveGame, SIGNAL(roundsRoundAdded(Round*)), this, SLOT(addRound(Round*)));

    foreach(Player *player, m_doppelkopfLiveGame->players()) {
        insertColumn(columnCount());
        QPixmap pixmap(140,140);
        pixmap.fill(player->color());
        setHorizontalHeaderItem(columnCount()-1,new QTableWidgetItem(QIcon(pixmap),player->name()));
    }

    insertColumn(columnCount());
    setHorizontalHeaderItem(columnCount()-1,new QTableWidgetItem(tr("")));

    insertColumn(columnCount());
    setHorizontalHeaderItem(columnCount()-1,new QTableWidgetItem(tr("")));

    foreach(Round *round, m_doppelkopfLiveGame->rounds()) {
        addRound(round);
    }
}

void PointsTable::addRound(Round* round)
{
    DoppelkopfRound* dokoround = static_cast<DoppelkopfRound*>(round);
    if(dokoround->state() != Round::Finished) {
        connect(dokoround, SIGNAL(stateChanged(Round::State)), this, SLOT(addLastRound()));
        return;
    }

    insertRow(rowCount());
    int column = 0;
    foreach(Player* p, m_doppelkopfLiveGame->players()) {
        PointsTablePlayerItem* item = new PointsTablePlayerItem(p,dokoround);
        setItem(rowCount()-1, column, item);
        ++column;
    }


    PointsTableTotalItem* item = new PointsTableTotalItem(dokoround);
    setItem(rowCount()-1,column++,item);

    QTableWidgetItem* item1 = new QTableWidgetItem();
    item1->setFlags(item->flags() & ~Qt::ItemIsSelectable & ~Qt::ItemIsEditable);
    if(!round->comment().isEmpty()) {
        item1->setText("C");
        item1->setToolTip(round->comment());
    }
    setItem(rowCount()-1, column, item1);

    item1 = new QTableWidgetItem("");
    item1->setSizeHint(QSize(0,0));
    setVerticalHeaderItem(rowCount()-1,item1);

    scrollToBottom();
}

void PointsTable::addLastRound()
{
    addRound(m_doppelkopfLiveGame->rounds().last());
}

PointsTableItem* PointsTable::itemAtIndex(const QModelIndex& index)
{
    return static_cast<PointsTableItem*>(item(index.row(),index.column()));
}

void PointsTable::resizeEvent(QResizeEvent* event)
{
    Q_UNUSED(event)
    if(!m_doppelkopfLiveGame)
        return;

    double w = (width() / (0.5 + m_doppelkopfLiveGame->players().size()) );

    for (int i = 0;  i < columnCount()-2; i++) {
        setColumnWidth(i,w-3);
        horizontalHeaderItem(i)->setSizeHint(QSize(w,50));
    }
    setColumnWidth(columnCount()-1, w / 8);
    setColumnWidth(columnCount()-1, w / 8);
    QTableWidget::resizeEvent(event);
}

}

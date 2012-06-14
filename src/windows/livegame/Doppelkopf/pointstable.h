#ifndef DOKOLIVEGAMEWINDOWNS_POINTSTABLE_H
#define DOKOLIVEGAMEWINDOWNS_POINTSTABLE_H

#include <QTableWidget>

class DoppelkopfLiveGame;
class Round;

namespace DokoLiveGameWindowNS {

class PointsTableItem;

class PointsTable : public QTableWidget
{
    Q_OBJECT

public:
    PointsTable(QWidget *parent = 0);

    void setDoppelkopfLiveGame(DoppelkopfLiveGame *doppelkopfLiveGame);

    void resizeEvent(QResizeEvent *event);

    PointsTableItem *itemAtIndex(const QModelIndex &index);

private slots:
    void addRound(Round *round);

private:
    DoppelkopfLiveGame *m_doppelkopfLiveGame;

};

}

#endif // DOKOLIVEGAMEWINDOWNS_POINTSTABLE_H

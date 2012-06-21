#ifndef DOKOLIVE
#define GUI_DETAILS_LIVEGAMEDETAILS_DOKOLIVEGAMEDETAILS_DOKOLIVEGAMEROUNDTABLEITEM_H

#include <QTableWidgetItem>
#include <QObject>

class Player;
class DoppelkopfRound;

namespace DokoLiveGameWindowNS {

class PointsTableItem : public QObject, public QTableWidgetItem
{
    Q_OBJECT
public:
    explicit PointsTableItem(DoppelkopfRound* round);

    virtual int points() const = 0;
    virtual void setPoints(int points) = 0;

protected:
    DoppelkopfRound *m_doppelkopfRound;
};

class PointsTablePlayerItem : public PointsTableItem
{
    Q_OBJECT
public:
    explicit PointsTablePlayerItem(Player* player, DoppelkopfRound* round);

    int points() const;
    void setPoints(int points);

private slots:
    void onPointsChanged(const Player *, int);

private:
    Player* m_player;
};

class PointsTableTotalItem : public PointsTableItem
{
    Q_OBJECT
public:
    explicit PointsTableTotalItem(DoppelkopfRound* round);

    int points() const;
    void setPoints(int points);

private slots:
    void onPointsChanged();
};

}

#endif // GUI_DETAILS_LIVEGAMEDETAILS_DOKOLIVEGAMEDETAILS_DOKOLIVEGAMEROUNDTABLEITEM_H

#ifndef PLAYERSLISTWIDGET_H
#define PLAYERSLISTWIDGET_H

#include <QListWidget>

class Player;
class PlayersContext;

class PlayersListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit PlayersListWidget(PlayersContext *context, QWidget *parent = 0);

    void addPlayer(Player *player);
    void addPlayers(QList<Player *> players);
    QList<Player *> selectedPlayers() const;
    QList<Player *> players() const;

    void removeSelectedPlayers();

    void transferSelectedPlayersFrom(PlayersListWidget *other);

public slots:
    void clear();

private:
    PlayersContext *m_context;

    QList<int> m_playerPositions;
};

#endif // PLAYERSLISTWIDGET_H

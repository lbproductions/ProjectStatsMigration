#ifndef PLAYERSCOMBOBOX_H
#define PLAYERSCOMBOBOX_H

#include <QComboBox>

class Player;

class PlayersComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit PlayersComboBox(QWidget *parent = 0);

    void addPlayers(QList<Player *> players);
    void addPlayer(Player * const player);

    QList<Player *> players() const;
    Player *currentPlayer() const;
    void setCurrentPlayer(Player *player);

    void removePlayer(Player *player);

private:
    QList<Player *> m_players;
    
};

#endif // PLAYERSCOMBOBOX_H

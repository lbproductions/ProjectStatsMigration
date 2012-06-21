#include "playercalculator.h"

#include "player.h"

#include "game.h"
#include "livegame.h"
#include "round.h"

#include <QDateTime>

PlayerCalculator::PlayerCalculator(QObject *parent) :
	Calculator(parent)
{
}

QVariant PlayerCalculator::lastGame(const LBDatabase::Entity *entity) const
{
	const Player *player = static_cast<const Player *>(entity);
    QList<Game *> list = player->relation<Game>(PlayerProperties::GamesRelation)->sort<QDateTime>(GameProperties::DateAttribute, LBDatabase::SortDescending);

    if(list.isEmpty())
        return QVariant();

    return list.first()->date();
}

QVariant PlayerCalculator::lastWin(const LBDatabase::Entity *entity) const
{
    const Player *player = static_cast<const Player *>(entity);
    QList<Game *> list = player->relation<Game>(PlayerProperties::GamesRelation)->sort<QDateTime>(GameProperties::DateAttribute, LBDatabase::SortDescending);

    if(list.isEmpty())
        return QVariant();

    foreach(Game *game, list) {
        if(game->placement(player) == 1) {
            return QVariant::fromValue<QDateTime>(game->date());
        }
    }

    return QVariant();
}

QVariant PlayerCalculator::averagePlacement(const LBDatabase::Entity *entity) const
{
	const Player *player = static_cast<const Player *>(entity);

    if(player->gameCount() == 0)
        return QVariant();

    int placementSum = 0;
    foreach(Game *game, player->games()) {
        placementSum += game->placement(player);
    }

    return QVariant((double)placementSum / player->gameCount());
}

QVariant PlayerCalculator::losses(const LBDatabase::Entity *entity) const
{
	const Player *player = static_cast<const Player *>(entity);
    int count = 0;
    foreach(Game *game, player->games()) {
        if(game->placement(player) == game->players().size())
            ++count;
    }
    return QVariant(count);
}

QVariant PlayerCalculator::wins(const LBDatabase::Entity *entity) const
{
	const Player *player = static_cast<const Player *>(entity);
    int count = 0;
    foreach(Game *game, player->games()) {
        if(game->placement(player) == 1)
            ++count;
    }
    return QVariant(count);
}

QVariant PlayerCalculator::diffAverageWeightedAverage(const LBDatabase::Entity *entity) const
{
    const Player *player = static_cast<const Player *>(entity);
    return QVariant(player->weightedAverage() - player->average());
}

QVariant PlayerCalculator::weightedAverage(const LBDatabase::Entity *entity) const
{
	const Player *player = static_cast<const Player *>(entity);
    double points = 0;
    double weight = 0.0;
    foreach(Game* g, player->games()){
        double zaehler = (double)(g->players().size() - g->placement(player));
        double nenner = (double)g->players().size()-1;
        double point = zaehler*100.0/nenner;
        QDateTime date = g->date();
        double yearsTo = (double)(date.date().daysTo(QDate::currentDate()));
        if(yearsTo < 3*365){
            if(yearsTo < 2* 365){
                if(yearsTo < 365){
                    if(yearsTo < 200){
                        if(yearsTo < 100){
                            if(yearsTo < 50){
                                if(yearsTo < 14){
                                    weight += 1;
                                }
                                else{
                                    weight += 0.9;
                                    point = point * 0.9;
                                }
                            }
                            else{
                                weight += 0.8;
                                point = point * 0.8;
                            }
                        }
                        else{
                            weight += 0.7;
                            point = point * 0.7;
                        }
                    }
                    else{
                        weight += 0.55;
                        point = point * 0.55;
                    }
                }
                else{
                    weight += 0.4;
                    point = point * 0.4;
                }
            }
            else{
                weight += 0.25;
                point = point * 0.25;
            }
        }
        else{
            weight += 0.1;
            point = point * 0.1;
        }

        points += point;
    }

    return QVariant(points/weight);
}

QVariant PlayerCalculator::average(const LBDatabase::Entity *entity) const
{
	const Player *player = static_cast<const Player *>(entity);
    return QVariant((double) player->points() / player->gameCount());
}

QVariant PlayerCalculator::gamePoints(const LBDatabase::Entity *entity) const
{
	const Player *player = static_cast<const Player *>(entity);
    int points = 0;
    foreach(Game *g, player->games()) {
        points += g->points(player);
    }

    return QVariant(points);
}

QVariant PlayerCalculator::points(const LBDatabase::Entity *entity) const
{
    const Player *player = static_cast<const Player *>(entity);
    int points = 0;
    foreach(Game *g, player->games()) {
        double zaehler = (double)(g->players().size() - g->placement(player));
        double nenner = (double)g->players().size() - 1;

        points += (int)(100* (zaehler / nenner));
    }
    return QVariant(points);
}

QVariant PlayerCalculator::gameCount(const LBDatabase::Entity *entity) const
{
	const Player *player = static_cast<const Player *>(entity);
    return QVariant(player->games().size());
}

RelatedEntities PlayerCalculator::roundsDealt(const LBDatabase::Entity *entity) const
{
	const Player *player = static_cast<const Player *>(entity);
    RelatedEntities rounds;

    foreach(Game *game, player->games()) {
        LiveGame *g = static_cast<LiveGame *>(game);
        for(int i = g->players().indexOf(const_cast<Player *const>(player)); i < g->rounds().size(); i += g->players().size()) {
            rounds.append(g->rounds().at(i));
        }
    }

    return rounds;
}

// NEW METHODS HERE. DO NOT DELETE THIS LINE!

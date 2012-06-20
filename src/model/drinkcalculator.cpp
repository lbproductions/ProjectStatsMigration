#include "drinkcalculator.h"

#include "drink.h"
#include "livedrink.h"
#include "player.h"

#include <LBDatabase/LBDatabase.h>

#include <QDebug>

DrinkCalculator::DrinkCalculator(QObject *parent) :
    Calculator(parent)
{
}

QVariant DrinkCalculator::drinkCount(const LBDatabase::Entity *entity) const
{
    const Drink *drink = static_cast<const Drink *>(entity);
    return QVariant(drink->liveDrinks().size());
}

EntityVariantHash DrinkCalculator::countPerPlayer(const LBDatabase::Entity *entity) const
{
	const Drink *drink = static_cast<const Drink *>(entity);
    EntityVariantHash result;

    foreach(LiveDrink *ld, drink->liveDrinks()) {
        Player *p = ld->player();
        result.insert(p, QVariant(result.value(p).toInt() + 1));
    }

    return result;
}

QVariant DrinkCalculator::mostDrinks(const LBDatabase::Entity *entity) const
{
	const Drink *drink = static_cast<const Drink *>(entity);
    QList<Player *> list = drink->relation<Player>(DrinkProperties::PlayersRelation)->sort<int>(drink->function(DrinkProperties::CountPerPlayerFunction),LBDatabase::SortDescending);
    if(list.isEmpty())
        return tr("No drinks");

    QList<Player *> result;
    int count = -1;
    foreach(Player *p , list) {
        if(count == -1)
            count = drink->countPerPlayer(p);
        if(count == drink->countPerPlayer(p))
            result.append(p);
    }

    if(result.size() == 1)
        return QVariant(result.first()->displayName() + QLatin1String(" (")+QString::number(count*100 / drink->drinkCount()) + QLatin1String("%)"));

    return QVariant(QString::number(result.size())+QLatin1String(" Players") + QLatin1String(" (")+QString::number(count*100 / drink->drinkCount()) + QLatin1String("%)"));
}

// NEW METHODS HERE. DO NOT DELETE THIS LINE!

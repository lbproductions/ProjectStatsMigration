#ifndef PLAYERDRINKSGROUPBOX_H
#define PLAYERDRINKSGROUPBOX_H

#include <LBGui/LBGui.h>

class Player;
class LiveDrink;
class LiveGame;

namespace LiveGameWindowNS {

class DrinkLabel : public LBGui::Label
{
    Q_OBJECT
public:
    explicit DrinkLabel(QWidget* parent);

    void setDrink(LiveDrink *drink);

signals:
    void drinkDoubleClicked(LiveDrink*);

private slots:
    void on_doubleClicked();

private:
    LiveDrink* m_drink;
};

class PlayerDrinksGroupBox : public LBGui::GroupBox
{
    Q_OBJECT
public:
    PlayerDrinksGroupBox(QWidget *parent = 0);

    void setPlayer(Player *player);
    void setLiveGame(LiveGame *liveGame);

private slots:
    void updateDrinks();
    void onDrinkDoubleClicked(LiveDrink*);

private:
    void setName(const QString &name);

    LBGui::Label *m_nameLabel;
    Player *m_player;
    LiveGame *m_liveGame;

    QGridLayout *m_drinksLayout;
};

}

#endif // PLAYERDRINKSGROUPBOX_H

#ifndef PLAYERDRINKSGROUPBOX_H
#define PLAYERDRINKSGROUPBOX_H

#include <LBGui/LBGui.h>

class Player;
class LiveDrink;
class LiveGame;
class Drink;

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

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void dragMoveEvent(QDragMoveEvent *);
    void dragLeaveEvent(QDragLeaveEvent *);

private slots:
    void updateDrinks();
    void onDrinkDoubleClicked(LiveDrink*);

private:
    void setName(const QString &name);

    void addDrink(Drink *drink);

    LBGui::Label *m_nameLabel;
    Player *m_player;
    LiveGame *m_liveGame;

    QGridLayout *m_drinksLayout;
    QWidget *m_centralWidget;
};

}

#endif // PLAYERDRINKSGROUPBOX_H

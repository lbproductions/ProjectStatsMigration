#include "playerdrinksgroupbox.h"

#include <model/player.h>
#include <model/drink.h>
#include <model/livedrink.h>
#include <model/livegame.h>
#include <model/livedrinkscontext.h>

namespace LiveGameWindowNS {

DrinkLabel::DrinkLabel(QWidget *parent) :
    Label(QString(), parent),
    m_drink(0)
{
    connect(this,SIGNAL(doubleClicked()),this,SLOT(on_doubleClicked()));
}

void DrinkLabel::setDrink(LiveDrink *drink)
{
    m_drink = drink;
    Drink* d = drink->drink();
    QPixmap pixmap = d->icon();
    if(pixmap.isNull())
        pixmap = QPixmap(":/drinks/beer_default");

    setPixmap(pixmap.scaled(20,45,Qt::KeepAspectRatio,Qt::SmoothTransformation));
    setToolTip(d->name() + QLatin1String(" ") + QString::number(d->size()) + tr("l - doubleclick to drink another"));
}

void DrinkLabel::on_doubleClicked()
{
    emit drinkDoubleClicked(m_drink);
}

PlayerDrinksGroupBox::PlayerDrinksGroupBox(QWidget *parent) :
    GroupBox(parent),
    m_player(0),
    m_liveGame(0)
{
    setStyle(GroupBox::IphotoDark);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    QVBoxLayout *l = new QVBoxLayout(centralWidget);
    l->setAlignment(Qt::AlignCenter);
    centralWidget->setLayout(l);

    m_nameLabel = new LBGui::Label(QString(), this);
    m_nameLabel->setForegroundColor(QColor(251,251,251));
    m_nameLabel->setDropshadowColor(QColor(67,67,67));
    m_nameLabel->setFont(QFont("Lucida Grande", 12, QFont::Bold));
    l->addWidget(m_nameLabel);

//    QFrame *line = new QFrame(this);
//    line->setGeometry(QRect(320, 150, 118, 1));
//    line->setFrameShape(QFrame::HLine);
//    line->setFrameShadow(QFrame::Sunken);
//    l->addWidget(line);

    m_drinksLayout = new QGridLayout();
    l->addLayout(m_drinksLayout);

    layout()->addWidget(centralWidget);
}

void PlayerDrinksGroupBox::setPlayer(Player *player)
{
    m_player = player;
    setName(player->name());
    updateDrinks();
    connect(player, SIGNAL(liveDrinksLiveDrinkAdded(LiveDrink*)), this, SLOT(updateDrinks()));
}

void PlayerDrinksGroupBox::setLiveGame(LiveGame *liveGame)
{
    m_liveGame = liveGame;
    updateDrinks();
}

void PlayerDrinksGroupBox::setName(const QString &name)
{
    m_nameLabel->setText(name);
}

void PlayerDrinksGroupBox::updateDrinks()
{
    if(!m_player || !m_liveGame)
        return;

    QLayoutItem *item;
    while((item = m_drinksLayout->takeAt(0))) {
        if(item->widget()) {
            item->widget()->setVisible(false);
            item->widget()->deleteLater();
        }
    }

    int drinks = 0;
    foreach(LiveDrink* drink, m_liveGame->drinksPerPlayer(m_player)) {
        DrinkLabel* drinkIcon = new DrinkLabel(this);
        drinkIcon->setDrink(drink);
        connect(drinkIcon,SIGNAL(drinkDoubleClicked(LiveDrink*)),this,SLOT(onDrinkDoubleClicked(LiveDrink*)));
        m_drinksLayout->addWidget(drinkIcon,(drinks/5),drinks%5,Qt::AlignCenter);
        drinks++;
    }
}

void PlayerDrinksGroupBox::onDrinkDoubleClicked(LiveDrink *drink)
{
    LiveDrink *newDrink = static_cast<LiveDrinksContext *>(drink->context())->createLiveDrink();
    newDrink->setDrink(drink->drink());
    newDrink->setRound(m_liveGame->rounds().last());
    m_player->addLiveDrink(newDrink);
}

}

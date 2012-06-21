#include "playerdrinksgroupbox.h"

#include <model/player.h>
#include <model/drink.h>
#include <model/livedrink.h>

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
//    QImage image = d->icon().pixmap(45);
//    if(image.isNull())
//    {
//        image = QImage(":graphics/drinks/default");
//    }
//    setPixmap(QPixmap::fromImage(image.scaled(20,45,Qt::KeepAspectRatio,Qt::SmoothTransformation)));
//    setToolTip(d->name() + QLatin1String(" ") + QString::number(d->size()) + tr("l - doubleclick to drink another"));
}

void DrinkLabel::on_doubleClicked()
{
    emit drinkDoubleClicked(m_drink);
}

PlayerDrinksGroupBox::PlayerDrinksGroupBox(QWidget *parent) :
    GroupBox(parent)
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

    QFrame *line = new QFrame(this);
    line->setGeometry(QRect(320, 150, 118, 1));
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    l->addWidget(line);

    layout()->addWidget(centralWidget);

    m_drinksLayout = new QGridLayout();
    l->addLayout(m_drinksLayout);
}

void PlayerDrinksGroupBox::setPlayer(Player *player)
{
    m_player = player;
    setName(player->name());
}

void PlayerDrinksGroupBox::setName(const QString &name)
{
    m_nameLabel->setText(name);
}

void PlayerDrinksGroupBox::updateDrinks()
{
    int drinks = 0;
//    foreach(LiveDrink* drink, livegame->drinksPerPlayer(player))
//    {
//        DrinkLabel* drinkIcon = new DrinkLabel(this);
//        drinkIcon->setDrink(drink);
//        connect(drinkIcon,SIGNAL(drinkDoubleClicked(::Database::LiveGameDrink*)),this,SLOT(ondrinkdoubleClicked(::Database::LiveGameDrink*)));
//    ui->gridLayoutDrinks->addWidget(drinkIcon,(drinks/5),drinks%5,Qt::AlignCenter);
//        drinks++;
//    }
}

}

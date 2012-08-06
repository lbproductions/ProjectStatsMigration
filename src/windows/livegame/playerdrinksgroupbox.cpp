#include "playerdrinksgroupbox.h"

#include <model/player.h>
#include <model/drink.h>
#include <model/drinkscontext.h>
#include <model/livedrink.h>
#include <model/livegame.h>
#include <model/livedrinkscontext.h>
#include <model/storage.h>

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>

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

    m_centralWidget = new QWidget(this);
    m_centralWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    QVBoxLayout *l = new QVBoxLayout(m_centralWidget);
    l->setAlignment(Qt::AlignCenter);
    m_centralWidget->setLayout(l);

    m_nameLabel = new LBGui::Label(QString(), this);
    m_nameLabel->setForegroundColor(QColor(251,251,251));
    m_nameLabel->setDropshadowColor(QColor(67,67,67));
    m_nameLabel->setFont(QFont("Lucida Grande", 12, QFont::Bold));
    m_nameLabel->setAlignment(Qt::AlignHCenter);
    l->addWidget(m_nameLabel);

//    QFrame *line = new QFrame(this);
//    line->setGeometry(QRect(320, 150, 118, 1));
//    line->setFrameShape(QFrame::HLine);
//    line->setFrameShadow(QFrame::Sunken);
//    l->addWidget(line);

    m_drinksLayout = new QGridLayout();
    l->addLayout(m_drinksLayout);

    layout()->addWidget(m_centralWidget);

    setAcceptDrops(true);
}

void PlayerDrinksGroupBox::setPlayer(Player *player)
{
    m_player = player;
    setName(player->name());
    updateDrinks();
    connect(player, SIGNAL(liveDrinksChanged()), this, SLOT(updateDrinks()));
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

void PlayerDrinksGroupBox::addDrink(Drink *drink)
{
    LiveDrinksContext *c = static_cast<Storage *>(m_player->entityType()->context()->storage())->liveDrinksContext();
    LiveDrink *newDrink = c->createLiveDrink();
    newDrink->setDrink(drink);
    newDrink->setRound(m_liveGame->rounds().last());
    m_player->addLiveDrink(newDrink);
}

void PlayerDrinksGroupBox::updateDrinks()
{
    if(!m_player || !m_liveGame)
        return;

    QLayoutItem *item;
    while((item = m_drinksLayout->takeAt(0))) {
        if(item->widget()) {
            item->widget()->setVisible(false);
        }
    }

    QString mimeType("application/projectstats.livegame/drink");

    int drinks = 0;
    foreach(LiveDrink* drink, m_liveGame->drinksPerPlayer(m_player)) {
        DrinkLabel* drinkIcon = new DrinkLabel(this);
        drinkIcon->setDrink(drink);
        drinkIcon->setMimeType(mimeType);
        drinkIcon->setMimeData(drink->drink()->id());
        drinkIcon->setDragEnabled(true);
        connect(drinkIcon,SIGNAL(drinkDoubleClicked(LiveDrink*)),this,SLOT(onDrinkDoubleClicked(LiveDrink*)));
        m_drinksLayout->addWidget(drinkIcon,(drinks/5),drinks%5,Qt::AlignCenter);
        drinks++;

        if(drinks % 5 == 0) {
            QWidget *spacer = new QWidget(this);
            spacer->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
            m_drinksLayout->addWidget(spacer,(drinks/5), 6);
        }
    }

    if(drinks == 0) {
        QLabel *label = new QLabel("No drinks");
        QFont f("Lucida Grande", 10, QFont::Normal, true);
        label->setFont(f);
        label->setStyleSheet("QLabel {color: #999; }");
        m_drinksLayout->addWidget(label, 0, 0);

        QWidget *spacer = new QWidget(this);
        spacer->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
        m_drinksLayout->addWidget(spacer,1,0);
    }
    else if(drinks < 5) {
        QWidget *spacer = new QWidget(this);
        spacer->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
        m_drinksLayout->addWidget(spacer,1,drinks);
    }
}

void PlayerDrinksGroupBox::onDrinkDoubleClicked(LiveDrink *drink)
{
    addDrink(drink->drink());
}

void PlayerDrinksGroupBox::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/projectstats.livegame/drink")) {
        m_centralWidget->setStyleSheet("QWidget { background: rgb(51,51,51); }");
        event->acceptProposedAction();
        repaint();
    }
}

void PlayerDrinksGroupBox::dropEvent(QDropEvent *event)
{
    QByteArray encodedData = event->mimeData()->data("application/projectstats.livegame/drink");
    QDataStream stream(&encodedData, QIODevice::ReadOnly);
    int id = -1;
    QVariant data;
    stream >> data;
    id = data.toInt();

    event->acceptProposedAction();

    DrinksContext *c = static_cast<Storage *>(m_player->entityType()->context()->storage())->drinksContext();
    Drink *d = c->drink(id);
    if(d) {
        if(event->keyboardModifiers() == Qt::ShiftModifier){
//            ChooseDrinkCountDialog dialog(d,m_player,m_livegame);
//            dialog.exec();
        }
        else{
            addDrink(d);
        }
    }
    m_centralWidget->setStyleSheet(QString());
}

void PlayerDrinksGroupBox::dragMoveEvent(QDragMoveEvent * /*event*/)
{
}

void PlayerDrinksGroupBox::dragLeaveEvent(QDragLeaveEvent * /*event*/)
{
    m_centralWidget->setStyleSheet(QString());
}

}

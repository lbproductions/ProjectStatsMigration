#include "livegamegeneraloptionswidget.h"
#include "ui_livegamegeneraloptionswidget.h"

#include "newgamewizard.h"
#include "chooseunfinishedgamedialog.h"

#include "../../widgets/placescombobox.h"
#include "../../widgets/playerslistwidget.h"
#include "../../model/doppelkopflivegame.h"
#include "../../model/player.h"
#include "../../model/playerscontext.h"
#include "../../model/storage.h"

#include <QSettings>

namespace Wizards {

namespace NewGame {

LiveGameGeneralOptionsWidget::LiveGameGeneralOptionsWidget(NewGameWizard *parent) :
    QWizardPage(parent),
    ui(new Ui::LiveGameGeneralOptionsWidget),
    m_wizard(parent)
{
    ui->setupUi(this);

    setupWidget();

    registerField("live_type", ui->comboBoxGameType,"currentText",SIGNAL(currentTextChanged()));

    connect(ui->comboBoxGameType,SIGNAL(currentIndexChanged(int)),this,SIGNAL(completeChanged()));
    connect(placesbox,SIGNAL(currentIndexChanged(int)),this,SIGNAL(completeChanged()));
    connect(ui->pushButtonDeselect,SIGNAL(clicked()),this,SIGNAL(completeChanged()));
    connect(ui->pushButtonSelect,SIGNAL(clicked()),this,SIGNAL(completeChanged()));

    setTitle(tr("Start a new game"));
}

LiveGameGeneralOptionsWidget::~LiveGameGeneralOptionsWidget()
{
    saveOptions();
    delete ui;
}

void LiveGameGeneralOptionsWidget::saveOptions() const
{
    QSettings settings;
    settings.setValue("LiveGameGeneralOptionsWidget/comboBoxGameTypeSelectedType",ui->comboBoxGameType->currentText());
    settings.setValue("LiveGameGeneralOptionsWidget/placesboxSelectedPlace",placesbox->currentText());
}

int LiveGameGeneralOptionsWidget::nextId() const
{
    saveOptions();

    if (ui->comboBoxGameType->currentText() == DoppelkopfLiveGame::GameName)
        return NewGameWizard::Page_LiveGameDokoOptions;

    return NewGameWizard::Page_LiveGameGeneralOptions;
}

void LiveGameGeneralOptionsWidget::setupWidget()
{
    ui->comboBoxGameType->clear();
    ui->comboBoxGameType->addItem(DoppelkopfLiveGame::GameName);

    QSettings settings;
    int selectedIndex = ui->comboBoxGameType->findText(settings.value("LiveGameGeneralOptionsWidget/comboBoxGameTypeSelectedType",tr("Choose a game...")).toString());
    selectedIndex = selectedIndex == -1 ? 0 : selectedIndex;
    ui->comboBoxGameType->setCurrentIndex(selectedIndex);

    m_availablePlayersList = new PlayersListWidget(m_wizard->storage()->playersContext());
    ui->verticalLayoutLeft->insertWidget(0,m_availablePlayersList);
    m_chosenPlayersList = new PlayersListWidget(m_wizard->storage()->playersContext());
    ui->verticalLayoutRight->insertWidget(0, m_chosenPlayersList);

    m_availablePlayersList->addPlayers(m_wizard->storage()->playersContext()->players());

    m_availablePlayersList->setAlternatingRowColors(true);
    m_chosenPlayersList->setAlternatingRowColors(true);

    placesbox = new PlacesComboBox(m_wizard->storage()->placesContext(), this);

    selectedIndex = placesbox->findText(settings.value("LiveGameGeneralOptionsWidget/placesboxSelectedPlace","").toString());
    selectedIndex = selectedIndex == -1 ? 0 : selectedIndex;
    placesbox->setCurrentIndex(selectedIndex);
    ui->formLayout->addRow(tr("Place:"),placesbox);
}

QList<Player*> LiveGameGeneralOptionsWidget::selectedPlayers()
{
    return m_chosenPlayersList->players();
}

Place *LiveGameGeneralOptionsWidget::selectedPlace()
{
    return placesbox->currentPlace();
}

bool LiveGameGeneralOptionsWidget::isComplete() const
{
    int minPlayerCount = 1;

    if (ui->comboBoxGameType->currentText() == DoppelkopfLiveGame::GameName)
    {
        minPlayerCount = 4;
    }
//    else if(ui->comboBoxGameType->currentText() == "Skat")
//    {
//        minPlayerCount = 3;
//    }

    if(m_chosenPlayersList->count() < minPlayerCount)
    {
        return false;
    }

    return true;
}

void LiveGameGeneralOptionsWidget::on_pushButtonSelect_clicked()
{
    m_chosenPlayersList->transferSelectedPlayersFrom(m_availablePlayersList);
}

void LiveGameGeneralOptionsWidget::on_pushButtonDeselect_clicked()
{
    m_availablePlayersList->transferSelectedPlayersFrom(m_chosenPlayersList);
}

void LiveGameGeneralOptionsWidget::generatePlayerPositions()
{
//    QList<Database::Player*> players = minimumPlayerConstellation();

//    if(players.size() > 0){

//        ui->listWidgetSelectedPlayers->selectAll();
//        on_pushButtonDeselect_clicked();

//        foreach(Database::Player* player, players){
//            QListWidgetItem * item = ui->listWidgetAllPlayers->findItems(player->name->value(),Qt::MatchExactly).first();
//            item->setSelected(true);
//        }
//        on_pushButtonSelect_clicked();

//        this->repaint();

//    }
}

// QList<Player*> LiveGameGeneralOptionsWidget::minimumPlayerConstellation()
// {
////     qDebug() << "LiveGameGeneralOptionsWidget::minimumPlayerConstellation() started";

////     QList<Database::Player*> players = this->selectedPlayers();
////     AttributeVariant v;
////     v.setValue(players);
////     QString displayVariant = v.displayVariant().toString();

////     QMap<QString,int> map = Database::Games::instance()->playerPositionCount->value();
////     qDebug() << "Count of original constellation: " << map.value(displayVariant);

////     if(map.value(displayVariant) > 1){ //Get all Lists that contains only selected Players
////         QList<QString> lists; //contains just lists that contains only selected Players
////         foreach(QString string, map.keys()){
////             QList<Database::Player*> list = stringToPlayerList(string);
////             if(list.size()==players.size()){
////                 bool allPlayersInside = true;
////                 foreach(Database::Player* player, list){
////                     if(!players.contains(player)){
////                         allPlayersInside = false;
////                     }
////                 }
////                 if(allPlayersInside){
////                     lists.append(string);
////                 }
////             }
////         }
////         if(lists.size() == 0){
////             qWarning() << "No games found with this players!";
////             return QList<Database::Player*>();
////         }

////         //Get minimum count
////         QString generationList = displayVariant;
////         foreach(QString string, lists){
////             if(map.value(string) < map.value(generationList)){
////                 generationList = string;
////             }
////         }

////         qDebug() << generationList << " : " << map.value(generationList);

////         //Get final PlayerList
////         QList<Database::Player*> finalList = stringToPlayerList(generationList);

////         return finalList;
////     }
////     else{  //selected Players is already the minimum
////        qDebug() << "Original constellation used!";
////        return players;
////     }
// }

void LiveGameGeneralOptionsWidget::on_pushButtonGeneratePositions_clicked()
{
    generatePlayerPositions();
}

void LiveGameGeneralOptionsWidget::on_pushButton_clicked()
{
    ChooseUnfinishedGameDialog* dialog = new ChooseUnfinishedGameDialog(this->selectedPlayers(),static_cast<QWidget*>(this->parent()));
    connect(dialog,SIGNAL(accepted()),this,SLOT(on_chooseUnfinishedGamesDialogAccepted()));
    dialog->exec();
}

void LiveGameGeneralOptionsWidget::on_chooseUnfinishedGamesDialogAccepted(){
    this->wizard()->close();
}

}
}

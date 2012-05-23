#include "chooseunfinishedgamedialog.h"
#include "ui_chooseunfinishedgamedialog.h"

#include <QDateTime>

namespace Wizards {

namespace NewGame {

ChooseUnfinishedGameDialog::ChooseUnfinishedGameDialog(QList<Player*> list, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseUnfinishedGameDialog)
{
    ui->setupUi(this);

//    foreach(Database::Game* game, Database::Games::instance()->unfinishedGames->value()){
//        bool complete = true;
//        if(game->live->value()){
//            if(game->playersSortedByPosition->value().size() == list.size()){
//                foreach(Database::Player* player, list){
//                    if(!game->playersSortedByPosition->value().contains(player)){
//                       complete = false;
//                    }
//                }
//                if(complete){
//                    QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
//                    if(game->name->value() == ""){
//                        item->setText(game->date->value().toString());
//                    }
//                    else{
//                        item->setText(game->name->value());
//                    }
//                    item->setData(Qt::UserRole+1,game->id());

//                }
//            }
//        }
//    }
}

ChooseUnfinishedGameDialog::~ChooseUnfinishedGameDialog()
{
    delete ui;
}

void ChooseUnfinishedGameDialog::on_buttonBox_accepted()
{
//    if(ui->listWidget->selectedItems().isEmpty()){
//        return;
//    }
//    QListWidgetItem* item = ui->listWidget->selectedItems().first();

//    Database::Game* game = Database::Games::instance()->rowById(item->data(Qt::UserRole+1).toInt());

//    Details::RowWindow *newRowWindow = game->rowWindow();
//    if(newRowWindow)
//    {
//        newRowWindow->show();
//        return;
//    }

//    this->accept();
}

void ChooseUnfinishedGameDialog::on_buttonBox_rejected()
{
    this->reject();
}

void ChooseUnfinishedGameDialog::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
//    Database::Game* game = Database::Games::instance()->rowById(item->data(Qt::UserRole+1).toInt());

//    Details::RowWindow *newRowWindow = game->rowWindow();
//    if(newRowWindow)
//    {
//        newRowWindow->show();
//        this->accept();
//    }
}

}
}

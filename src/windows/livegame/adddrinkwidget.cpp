#include "adddrinkwidget.h"
#include "ui_adddrinkwidget.h"

#include <model/storage.h>
#include <model/drink.h>
#include <model/drinkscontext.h>

#include <LBGui/LBGui.h>

#include <QDialogButtonBox>

namespace LiveGameWindowNS {

AddDrinkWidget::AddDrinkWidget(Storage *storage, QWidget *parent) :
    QDialog(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);

    QString mimeType("application/projectstats.livegame/drink");

    setObjectName("dialog");
    this->setStyleSheet("QWidget#dialog { background-image: url(:/general/background_linen); } QLabel { color: white; } QGroupBox { color: white; }");

    QVBoxLayout* layout = new QVBoxLayout(this);

    QMultiMap<QString, Drink *> drinks = storage->drinksContext()->drinksByType();
    foreach(QString type, storage->drinksContext()->availableDrinkTypes()) {
        QWidget *w = new QWidget(this);
        QGridLayout* grid = new QGridLayout(this);
        w->setLayout(grid);
        //grid->addWidget(new QLabel(type,this),0,0);

        QList<Drink *> drinksOfType = drinks.values(type);
        int j = 0;
        foreach(Drink *d, drinksOfType) {
            QVBoxLayout* drink = new QVBoxLayout(this);

            LBGui::Label* name = new LBGui::Label(d->name(), this);
            name->setDragEnabled(true);
            name->setAlignment(Qt::AlignCenter);
            name->setMimeType(mimeType);
            name->setMimeData(d->id());

            LBGui::Label* icon = new LBGui::Label(QString(),this);
            icon->setDragEnabled(true);
            if(!d->icon().isNull())
                icon->setPixmap(d->icon().scaled(30,55,Qt::KeepAspectRatio,Qt::SmoothTransformation));
            else
                icon->setPixmap(QPixmap(":/drinks/beer_default").scaled(30,55,Qt::KeepAspectRatio,Qt::SmoothTransformation));
            icon->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
            icon->setAlignment(Qt::AlignCenter);
            icon->setMimeType(mimeType);
            icon->setMimeData(d->id());

            drink->addWidget(icon);
            drink->addWidget(name);

            grid->addLayout(drink,(j/7)+1,j%7);
            ++j;
        }
        for(; j%7 != 0; ++j) {
            QWidget *spacer = new QWidget(this);
            spacer->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
            grid->addWidget(spacer,(j/7)+1,j%7);
        }

        LBGui::GroupBox* box = new LBGui::GroupBox(this);
        box->setTitle(type);
        box->layout()->addWidget(w);
        layout->addWidget(box);
    }

    QDialogButtonBox *buttonBox = new QDialogButtonBox(this);
    buttonBox->setStandardButtons(QDialogButtonBox::Close);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    layout->addWidget(buttonBox);

//    foreach(QString type, Database::Drinks::instance()->types->value()){
//    }

//    QHBoxLayout* close = new QHBoxLayout(this);
//    close->addStretch();
//    QPushButton* closeButton = new QPushButton(tr("Close"),this);
//    connect(closeButton,SIGNAL(clicked()),this,SLOT(buttonCloseClicked()));
//    close->addWidget(closeButton);
//    close->addStretch();

//    layout->addLayout(close);

//    QList<Database::Drink*> drinklist = Database::Drinks::instance()->/*drinksByDrinkCount*/allRows();

    /*
    for (int i = 0; i<drinklist.size();i++)
    {
        QVBoxLayout* layout = new QVBoxLayout();
        DraggableLabel* label = new DraggableLabel(drinklist.at(i));
        label->setText(drinklist.at(i)->name->value());
        QFont font = label->font();
        font.setPointSize(font.pointSize()*((double)(Handler::getInstance()->getDesktopWidth())/1680.0));
        label->setFont(font);

        QHBoxLayout* iconlayout = new QHBoxLayout();
        iconlayout->addStretch();
        DraggableLabel* icon = new DraggableLabel(drinklist.at(i));
        icon->setPixmap(QPixmap::fromImage(drinklist.at(i)->icon->value().scaled(40*((double)(Handler::getInstance()->getDesktopWidth())/1680.0),100*((double)(Handler::getInstance()->getDesktopHeight())/1680.0),Qt::KeepAspectRatio,Qt::SmoothTransformation)));
        icon->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
        iconlayout->addWidget(icon);
        iconlayout->addStretch();
        layout->addLayout(iconlayout);
        layout->addWidget(label);
        ui->horizontalLayoutGroupBox->addLayout(layout);
    }

    */
}

}

#include "entitytypeview.h"
#include "ui_entitytypeview.h"

#include "attributesmodel.h"

#include <LBDatabase/LBDatabase.h>

namespace MainWindowNS {

EntityTypeView::EntityTypeView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EntityTypeView),
    m_entityType(0)
{
    ui->setupUi(this);
}

EntityTypeView::~EntityTypeView()
{
    delete ui;
}

void EntityTypeView::setEntityType(LBDatabase::EntityType *entityType)
{
    m_entityType = entityType;

    ui->labelId->setText(QString::number(entityType->id()));
    ui->lineEditDisplayName->setText(entityType->displayName());
    ui->lineEditIdentifier->setText(entityType->identifier());
    ui->comboBoxContext->addItem(entityType->context()->identifier());
    if(entityType->parentEntityType())
        ui->comboBoxParent->addItem(entityType->parentEntityType()->identifier());
    else
        ui->comboBoxParent->addItem("---");

    //Attributes
    QStandardItemModel *attributesModel = new QStandardItemModel(this);
    int row = 0;
    foreach(LBDatabase::Attribute *attribute, entityType->attributes()) {
        QStandardItem *itemName = new QStandardItem(attribute->identifier());
        attributesModel->setItem(row, 0, itemName);
        QStandardItem *itemType = new QStandardItem(attribute->qtType());
        attributesModel->setItem(row, 1, itemType);
        row++;
    }

    QStringList attributesHeaderTitles;
    attributesHeaderTitles << tr("Identifier") << tr("Qt-Type");
    attributesModel->setHorizontalHeaderLabels(attributesHeaderTitles);

    ui->treeViewAttributes->setModel(attributesModel);
    ui->treeViewAttributes->setHeaderHidden(false);

    //Functions
    QStandardItemModel *functionsModel = new QStandardItemModel(this);
    row = 0;
    foreach(LBDatabase::Function *function, entityType->functions()) {
        QStandardItem *itemName = new QStandardItem(function->identifier());
        functionsModel->setItem(row, 0, itemName);
//        QStandardItem *itemType = new QStandardItem(attribute->qtType());
//        functionsModel->setItem(row, 1, itemType);
        row++;
    }

    QStringList functionsHeaderTitles;
    functionsHeaderTitles << tr("Identifier");
    functionsModel->setHorizontalHeaderLabels(functionsHeaderTitles);

    ui->treeViewFunctions->setModel(functionsModel);
    ui->treeViewFunctions->setHeaderHidden(false);

    //Relations
    QStandardItemModel *relationsModel = new QStandardItemModel(this);
    row = 0;
    foreach(LBDatabase::Relation *relation, entityType->relations()) {
        QStandardItem *itemName = new QStandardItem(relation->identifier());
        relationsModel->setItem(row, 0, itemName);
//        QStandardItem *itemType = new QStandardItem(attribute->qtType());
//        relationsModel->setItem(row, 1, itemType);
        row++;
    }

    QStringList relationsHeaderTitles;
    relationsHeaderTitles << tr("Identifier");
    relationsModel->setHorizontalHeaderLabels(relationsHeaderTitles);

    ui->treeViewRelations->setModel(relationsModel);
    ui->treeViewRelations->setHeaderHidden(false);
}

} // namespace MainWindowNS

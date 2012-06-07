#include "entitytypeview.h"
#include "ui_entitytypeview.h"

#include "attributeeditor.h"

#include <LBDatabase/LBDatabase.h>

#include <QStandardItemModel>

#include <QDebug>

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
    m_attributesModel = new QStandardItemModel(this);
    int row = 0;
    foreach(LBDatabase::Attribute *attribute, entityType->attributes()) {
        QStandardItem *itemName = new QStandardItem(attribute->identifier());
        itemName->setData(QVariant::fromValue<LBDatabase::Attribute *>(attribute));
        m_attributesModel->setItem(row, 0, itemName);
        QStandardItem *itemType = new QStandardItem(attribute->qtType());
        m_attributesModel->setItem(row, 1, itemType);
        row++;
    }

    QStringList attributesHeaderTitles;
    attributesHeaderTitles << tr("Identifier") << tr("Qt-Type");
    m_attributesModel->setHorizontalHeaderLabels(attributesHeaderTitles);

    ui->treeViewAttributes->setModel(m_attributesModel);
    ui->treeViewAttributes->setHeaderHidden(false);

    //Functions
    m_functionsModel = new QStandardItemModel(this);
    row = 0;
    foreach(LBDatabase::Function *function, entityType->functions()) {
        QStandardItem *itemName = new QStandardItem(function->identifier());
        m_functionsModel->setItem(row, 0, itemName);
//        QStandardItem *itemType = new QStandardItem(attribute->qtType());
//        functionsModel->setItem(row, 1, itemType);
        row++;
    }

    QStringList functionsHeaderTitles;
    functionsHeaderTitles << tr("Identifier");
    m_functionsModel->setHorizontalHeaderLabels(functionsHeaderTitles);

    ui->treeViewFunctions->setModel(m_functionsModel);
    ui->treeViewFunctions->setHeaderHidden(false);

    //Relations
    m_relationsModel = new QStandardItemModel(this);
    row = 0;
    foreach(LBDatabase::Relation *relation, entityType->relations()) {
        QStandardItem *itemName = new QStandardItem(relation->identifier());
        m_relationsModel->setItem(row, 0, itemName);
//        QStandardItem *itemType = new QStandardItem(attribute->qtType());
//        relationsModel->setItem(row, 1, itemType);
        row++;
    }

    QStringList relationsHeaderTitles;
    relationsHeaderTitles << tr("Identifier");
    m_relationsModel->setHorizontalHeaderLabels(relationsHeaderTitles);

    ui->treeViewRelations->setModel(m_relationsModel);
    ui->treeViewRelations->setHeaderHidden(false);
}

} // namespace MainWindowNS

void MainWindowNS::EntityTypeView::on_pushButtonEditAttribute_clicked()
{
    if(ui->treeViewAttributes->selectionModel()->selectedRows(0).isEmpty())
        return;

    QStandardItem *item = m_attributesModel->itemFromIndex(ui->treeViewAttributes->selectionModel()->selectedRows(0).at(0));
    LBDatabase::Attribute *attribute = item->data().value<LBDatabase::Attribute *>();
    qDebug() << attribute->identifier();

    AttributeEditor *editor = new AttributeEditor();
    editor->setAttribute(attribute);
    editor->open();
}

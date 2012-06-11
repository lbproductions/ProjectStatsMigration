#include "entitytypeview.h"
#include "ui_entitytypeview.h"

#include "attributeeditor.h"
#include "functioneditor.h"
#include "relationseditor.h"

#include "../actions.h"
#include "../controller.h"
#include "../mainwindow.h"

#include <LBDatabase/LBDatabase.h>

#include <QStandardItemModel>
#include <QMessageBox>

#include <QDebug>

namespace MainWindowNS {

EntityTypeView::EntityTypeView(MainWindow *parent) :
    LBGui::View(parent),
    ui(new Ui::EntityTypeView),
    m_parent(parent),
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
    QList<LBDatabase::Attribute *> inheritedAttributes = entityType->attributes();
    m_attributesModel = new QStandardItemModel(this);
    int row = 0;
    foreach(LBDatabase::Attribute *attribute, entityType->nonInhertitedAttributes()) {
        inheritedAttributes.removeAll(attribute);
        QStandardItem *item = new QStandardItem(attribute->identifier());
        item->setData(QVariant::fromValue<LBDatabase::Attribute *>(attribute));
        item->setEditable(false);
        m_attributesModel->setItem(row, 0, item);
        item = new QStandardItem(attribute->typeName());
        item->setEditable(false);
        m_attributesModel->setItem(row, 1, item);
        item = new QStandardItem();
        item->setEditable(false);
        item->setCheckState(attribute->isCached() ? Qt::Checked : Qt::Unchecked);
        m_attributesModel->setItem(row, 2, item);
        item = new QStandardItem();
        item->setEditable(false);
        item->setCheckState(attribute->isCalculated() ? Qt::Checked : Qt::Unchecked);
        m_attributesModel->setItem(row, 3, item);
        item = new QStandardItem();
        item->setEditable(false);
        item->setCheckState(attribute->isEditable() ? Qt::Checked : Qt::Unchecked);
        m_attributesModel->setItem(row, 4, item);
        item = new QStandardItem(attribute->defaultValue().toString());
        item->setEditable(false);
        m_attributesModel->setItem(row, 5, item);
        row++;
    }

    if(!inheritedAttributes.isEmpty()) {
        QStandardItem *item = new QStandardItem(tr("Inherited Attributes:"));
        item->setEditable(false);
        item->setSelectable(false);
        item->setFont(QFont("Lucida Grande",12,QFont::Bold));
        item->setForeground(QBrush(QColor(150,150,150)));
        m_attributesModel->setItem(row, 0, item);
        item = new QStandardItem("");
        item->setEditable(false);
        item->setSelectable(false);
        m_attributesModel->setItem(row, 1, item);
        item = new QStandardItem("");
        item->setEditable(false);
        item->setSelectable(false);
        m_attributesModel->setItem(row, 2, item);
        item = new QStandardItem("");
        item->setEditable(false);
        item->setSelectable(false);
        m_attributesModel->setItem(row, 3, item);
        item = new QStandardItem("");
        item->setEditable(false);
        item->setSelectable(false);
        m_attributesModel->setItem(row, 4, item);
        item = new QStandardItem("");
        item->setEditable(false);
        item->setSelectable(false);
        m_attributesModel->setItem(row, 5, item);
        row++;
    }

    foreach(LBDatabase::Attribute *attribute, inheritedAttributes) {
        QStandardItem *item1 = new QStandardItem(attribute->identifier());
        item1->setData(QVariant::fromValue<LBDatabase::Attribute *>(attribute));
        item1->setEditable(false);
        m_attributesModel->setItem(row, 0, item1);
        QStandardItem *item2 = new QStandardItem(attribute->typeName());
        item2->setEditable(false);
        m_attributesModel->setItem(row, 1, item2);
        QStandardItem *item3 = new QStandardItem();
        item3->setEditable(false);
        item3->setCheckState(attribute->isCached() ? Qt::Checked : Qt::Unchecked);
        m_attributesModel->setItem(row, 2, item3);
        QStandardItem *item4 = new QStandardItem();
        item4->setEditable(false);
        item4->setCheckState(attribute->isCalculated() ? Qt::Checked : Qt::Unchecked);
        m_attributesModel->setItem(row, 3, item4);
        QStandardItem *item5 = new QStandardItem();
        item5->setEditable(false);
        item5->setCheckState(attribute->isEditable() ? Qt::Checked : Qt::Unchecked);
        m_attributesModel->setItem(row, 4, item5);
        QStandardItem *item6 = new QStandardItem(attribute->defaultValue().toString());
        item6->setEditable(false);
        m_attributesModel->setItem(row, 5, item6);
        row++;
    }

    QStringList attributesHeaderTitles;
    attributesHeaderTitles << tr("Identifier") << tr("Type") << tr("Cached") << tr("Calculated") << tr("Editable") << tr("Default Value");
    m_attributesModel->setHorizontalHeaderLabels(attributesHeaderTitles);

    ui->treeViewAttributes->setHeaderHidden(false);
    ui->treeViewAttributes->setUniformRowHeights(true);
    ui->treeViewAttributes->setAlternatingRowColors(true);
    ui->treeViewAttributes->setModel(m_attributesModel);
    ui->treeViewAttributes->resizeColumnToContents(0);
    ui->treeViewAttributes->resizeColumnToContents(1);
    ui->treeViewAttributes->resizeColumnToContents(2);
    ui->treeViewAttributes->resizeColumnToContents(3);
    ui->treeViewAttributes->resizeColumnToContents(4);
    ui->treeViewAttributes->resizeColumnToContents(5);

    //Functions
    m_functionsModel = new QStandardItemModel(this);
    QList<LBDatabase::Function *> inheritedFunctions= entityType->functions();
    row = 0;
    foreach(LBDatabase::Function *function, entityType->nonInhertitedFunctions()) {
        inheritedFunctions.removeAll(function);
        QStandardItem *item = new QStandardItem(function->identifier());
        item->setData(QVariant::fromValue<LBDatabase::Function *>(function));
        item->setEditable(false);
        m_functionsModel->setItem(row, 0, item);
        item = new QStandardItem(":");
        item->setEditable(false);
        m_functionsModel->setItem(row, 1, item);
        item = new QStandardItem(function->keyEntityType()->identifier());
        item->setEditable(false);
        m_functionsModel->setItem(row, 2, item);
        item = new QStandardItem("->");
        item->setEditable(false);
        m_functionsModel->setItem(row, 3, item);
        item = new QStandardItem(LBDatabase::Attribute::typeToName(function->type()));
        item->setEditable(false);
        m_functionsModel->setItem(row, 4, item);
        item = new QStandardItem();
        item->setEditable(false);
        item->setCheckState(function->isCached() ? Qt::Checked : Qt::Unchecked);
        m_functionsModel->setItem(row, 5, item);
        item = new QStandardItem();
        item->setEditable(false);
        item->setCheckState(function->isCalculated() ? Qt::Checked : Qt::Unchecked);
        m_functionsModel->setItem(row, 6, item);
        item = new QStandardItem();
        item->setEditable(false);
        item->setCheckState(function->isEditable() ? Qt::Checked : Qt::Unchecked);
        m_functionsModel->setItem(row, 7, item);
        row++;
    }

    if(!inheritedFunctions.isEmpty()) {
        QStandardItem *item = new QStandardItem(tr("Inherited Functions:"));
        item->setEditable(false);
        item->setSelectable(false);
        item->setFont(QFont("Lucida Grande",12,QFont::Bold));
        item->setForeground(QBrush(QColor(150,150,150)));
        m_functionsModel->setItem(row, 0, item);
        item = new QStandardItem("");
        item->setEditable(false);
        item->setSelectable(false);
        m_functionsModel->setItem(row, 1, item);
        item = new QStandardItem("");
        item->setEditable(false);
        item->setSelectable(false);
        m_functionsModel->setItem(row, 2, item);
        item = new QStandardItem("");
        item->setEditable(false);
        item->setSelectable(false);
        m_functionsModel->setItem(row, 3, item);
        item = new QStandardItem("");
        item->setEditable(false);
        item->setSelectable(false);
        m_functionsModel->setItem(row, 4, item);
        item = new QStandardItem("");
        item->setEditable(false);
        item->setSelectable(false);
        m_functionsModel->setItem(row, 5, item);
        item = new QStandardItem("");
        item->setEditable(false);
        item->setSelectable(false);
        m_functionsModel->setItem(row, 6, item);
        item = new QStandardItem("");
        item->setEditable(false);
        item->setSelectable(false);
        m_functionsModel->setItem(row, 7, item);
        row++;
    }

    foreach(LBDatabase::Function *function, inheritedFunctions) {
        QStandardItem *item = new QStandardItem(function->identifier());
        item->setData(QVariant::fromValue<LBDatabase::Function *>(function));
        item->setEditable(false);
        m_functionsModel->setItem(row, 0, item);
        item = new QStandardItem(":");
        item->setEditable(false);
        m_functionsModel->setItem(row, 1, item);
        item = new QStandardItem(function->keyEntityType()->identifier());
        item->setEditable(false);
        m_functionsModel->setItem(row, 2, item);
        item = new QStandardItem("->");
        item->setEditable(false);
        m_functionsModel->setItem(row, 3, item);
        item = new QStandardItem(LBDatabase::Attribute::typeToName(function->type()));
        item->setEditable(false);
        m_functionsModel->setItem(row, 4, item);
        item = new QStandardItem();
        item->setEditable(false);
        item->setCheckState(function->isCached() ? Qt::Checked : Qt::Unchecked);
        m_functionsModel->setItem(row, 5, item);
        item = new QStandardItem();
        item->setEditable(false);
        item->setCheckState(function->isCalculated() ? Qt::Checked : Qt::Unchecked);
        m_functionsModel->setItem(row, 6, item);
        item = new QStandardItem();
        item->setEditable(false);
        item->setCheckState(function->isEditable() ? Qt::Checked : Qt::Unchecked);
        m_functionsModel->setItem(row, 7, item);
        row++;
    }

    QStringList functionsHeaderTitles;
    functionsHeaderTitles << tr("Identifier") << "" << tr("Key Entity") << "" << tr("Type") << tr("Cached") << tr("Calculated") << tr("Editable");
    m_functionsModel->setHorizontalHeaderLabels(functionsHeaderTitles);

    ui->treeViewFunctions->setHeaderHidden(false);
    ui->treeViewFunctions->setUniformRowHeights(true);
    ui->treeViewFunctions->setAlternatingRowColors(true);
    ui->treeViewFunctions->setModel(m_functionsModel);
    ui->treeViewFunctions->resizeColumnToContents(0);
    ui->treeViewFunctions->resizeColumnToContents(1);
    ui->treeViewFunctions->resizeColumnToContents(2);
    ui->treeViewFunctions->resizeColumnToContents(3);
    ui->treeViewFunctions->resizeColumnToContents(4);
    ui->treeViewFunctions->setColumnWidth(4, ui->treeViewFunctions->columnWidth(4) + 100);
    ui->treeViewFunctions->resizeColumnToContents(5);
    ui->treeViewFunctions->resizeColumnToContents(6);
    ui->treeViewFunctions->resizeColumnToContents(7);

    //Relations
    m_relationsModel = new QStandardItemModel(this);

    QList<LBDatabase::Relation *> transposeRelations;
    QList<LBDatabase::Relation *> inheritedRelations = entityType->relations();

    row = 0;
    foreach(LBDatabase::Relation *relation, entityType->nonInhertitedRelations()) {
        inheritedRelations.removeAll(relation);
        if(relation->isTranspose()) {
            transposeRelations.append(relation);
            continue;
        }
        addRelationToModel(row, relation);
        row++;
    }

    if(!transposeRelations.isEmpty()) {
        QStandardItem *item = new QStandardItem(tr("Transpose Relations:"));
        item->setEditable(false);
        item->setSelectable(false);
        item->setFont(QFont("Lucida Grande",12,QFont::Bold));
        item->setForeground(QBrush(QColor(150,150,150)));
        m_relationsModel->setItem(row, 0, item);
        item = new QStandardItem("");
        item->setEditable(false);
        item->setSelectable(false);
        m_relationsModel->setItem(row, 1, item);
        item = new QStandardItem("");
        item->setEditable(false);
        item->setSelectable(false);
        m_relationsModel->setItem(row, 2, item);
        item = new QStandardItem("");
        item->setEditable(false);
        item->setSelectable(false);
        m_relationsModel->setItem(row, 3, item);
        item = new QStandardItem("");
        item->setEditable(false);
        item->setSelectable(false);
        m_relationsModel->setItem(row, 4, item);
        item = new QStandardItem("");
        item->setEditable(false);
        item->setSelectable(false);
        m_relationsModel->setItem(row, 5, item);
        item = new QStandardItem("");
        item->setEditable(false);
        item->setSelectable(false);
        m_relationsModel->setItem(row, 6, item);
        item = new QStandardItem("");
        item->setEditable(false);
        item->setSelectable(false);
        m_relationsModel->setItem(row, 7, item);
        row++;
    }

    foreach(LBDatabase::Relation *relation, transposeRelations) {
        addRelationToModel(row, relation);
        row++;
    }

    if(!inheritedRelations.isEmpty()) {
        QStandardItem *item = new QStandardItem(tr("Inherited Relations:"));
        item->setEditable(false);
        item->setSelectable(false);
        item->setFont(QFont("Lucida Grande",12,QFont::Bold));
        item->setForeground(QBrush(QColor(150,150,150)));
        m_relationsModel->setItem(row, 0, item);
        item = new QStandardItem("");
        item->setEditable(false);
        item->setSelectable(false);
        m_relationsModel->setItem(row, 1, item);
        item = new QStandardItem("");
        item->setEditable(false);
        item->setSelectable(false);
        m_relationsModel->setItem(row, 2, item);
        item = new QStandardItem("");
        item->setEditable(false);
        item->setSelectable(false);
        m_relationsModel->setItem(row, 3, item);
        item = new QStandardItem("");
        item->setEditable(false);
        item->setSelectable(false);
        m_relationsModel->setItem(row, 4, item);
        item = new QStandardItem("");
        item->setEditable(false);
        item->setSelectable(false);
        m_relationsModel->setItem(row, 5, item);
        item = new QStandardItem("");
        item->setEditable(false);
        item->setSelectable(false);
        m_relationsModel->setItem(row, 6, item);
        item = new QStandardItem("");
        item->setEditable(false);
        item->setSelectable(false);
        m_relationsModel->setItem(row, 7, item);
        row++;
    }

    QList<LBDatabase::Relation *> inheritedTransposeRelations;
    foreach(LBDatabase::Relation *relation, inheritedRelations) {
        if(relation->isTranspose()) {
            inheritedTransposeRelations.append(relation);
            continue;
        }
        addRelationToModel(row, relation);
        row++;
    }

    if(!inheritedTransposeRelations.isEmpty()) {
        QStandardItem *item = new QStandardItem(tr("Inherited Transpose Relations:"));
        item->setEditable(false);
        item->setSelectable(false);
        item->setFont(QFont("Lucida Grande",12,QFont::Bold));
        item->setForeground(QBrush(QColor(150,150,150)));
        m_relationsModel->setItem(row, 0, item);
        item = new QStandardItem("");
        item->setEditable(false);
        item->setSelectable(false);
        m_relationsModel->setItem(row, 1, item);
        item = new QStandardItem("");
        item->setEditable(false);
        item->setSelectable(false);
        m_relationsModel->setItem(row, 2, item);
        item = new QStandardItem("");
        item->setEditable(false);
        item->setSelectable(false);
        m_relationsModel->setItem(row, 3, item);
        item = new QStandardItem("");
        item->setEditable(false);
        item->setSelectable(false);
        m_relationsModel->setItem(row, 4, item);
        item = new QStandardItem("");
        item->setEditable(false);
        item->setSelectable(false);
        m_relationsModel->setItem(row, 5, item);
        item = new QStandardItem("");
        item->setEditable(false);
        item->setSelectable(false);
        m_relationsModel->setItem(row, 6, item);
        item = new QStandardItem("");
        item->setEditable(false);
        item->setSelectable(false);
        m_relationsModel->setItem(row, 7, item);
        row++;
    }

    foreach(LBDatabase::Relation *relation, inheritedTransposeRelations) {
        addRelationToModel(row, relation);
        row++;
    }

    QStringList relationsHeaderTitles;
    relationsHeaderTitles << tr("Identifier") << tr("Entity") << "" << "" << "" << tr("Related Entity") << tr("Calculated") << tr("Editable");
    m_relationsModel->setHorizontalHeaderLabels(relationsHeaderTitles);

    ui->treeViewRelations->setHeaderHidden(false);
    ui->treeViewRelations->setUniformRowHeights(true);
    ui->treeViewRelations->setAlternatingRowColors(true);
    ui->treeViewRelations->setModel(m_relationsModel);
    ui->treeViewRelations->resizeColumnToContents(0);
    ui->treeViewRelations->resizeColumnToContents(1);
    ui->treeViewRelations->resizeColumnToContents(2);
    ui->treeViewRelations->resizeColumnToContents(3);
    ui->treeViewRelations->resizeColumnToContents(4);
    ui->treeViewRelations->resizeColumnToContents(5);
    ui->treeViewRelations->resizeColumnToContents(6);
    ui->treeViewRelations->resizeColumnToContents(7);

    connect(ui->treeViewAttributes->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(attributeSelectionChanged(QModelIndex,QModelIndex)));
    connect(ui->treeViewFunctions->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(functionSelectionChanged(QModelIndex,QModelIndex)));
    connect(ui->treeViewRelations->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(relationSelectionChanged(QModelIndex,QModelIndex)));
}

void EntityTypeView::addRelationToModel(int row, LBDatabase::Relation *relation)
{
    QStandardItem *item = new QStandardItem(relation->identifier());
    item->setData(QVariant::fromValue<LBDatabase::Relation *>(relation));
    item->setEditable(false);
    m_relationsModel->setItem(row, 0, item);

    item = new QStandardItem(relation->entityType()->identifier());
    item->setEditable(false);
    m_relationsModel->setItem(row, 1, item);

    if(relation->isTranspose()) {
        item = new QStandardItem("<-");
        item->setEditable(false);
        m_relationsModel->setItem(row, 2, item);

        switch(relation->cardinality()) {
        case LBDatabase::Relation::OneToOne:
            item = new QStandardItem("1:1");
            break;
        case LBDatabase::Relation::OneToMany:
            item = new QStandardItem("N:1");
            break;
        default:
        case LBDatabase::Relation::ManyToMany:
            item = new QStandardItem("M:N");
            break;
        }
        item->setEditable(false);
        m_relationsModel->setItem(row, 3, item);

        item = new QStandardItem(relation->direction() == LBDatabase::Relation::Both ? "->" : "");
        item->setEditable(false);
        m_relationsModel->setItem(row, 4, item);
    }
    else {
        item = new QStandardItem(relation->direction() == LBDatabase::Relation::Both ? "<-" : "");
        item->setEditable(false);
        m_relationsModel->setItem(row, 2, item);

        switch(relation->cardinality()) {
        case LBDatabase::Relation::OneToOne:
            item = new QStandardItem("1:1");
            break;
        case LBDatabase::Relation::OneToMany:
            item = new QStandardItem("1:N");
            break;
        default:
        case LBDatabase::Relation::ManyToMany:
            item = new QStandardItem("N:M");
            break;
        }
        item->setEditable(false);
        m_relationsModel->setItem(row, 3, item);

        item = new QStandardItem("->");
        item->setEditable(false);
        m_relationsModel->setItem(row, 4, item);
    }

    item = new QStandardItem(relation->entityTypeOther()->identifier());
    item->setEditable(false);
    m_relationsModel->setItem(row, 5, item);

    item = new QStandardItem();
    item->setEditable(false);
    item->setCheckState(relation->isCalculated() ? Qt::Checked : Qt::Unchecked);
    m_relationsModel->setItem(row, 6, item);
    item = new QStandardItem();
    item->setEditable(false);
    item->setCheckState(relation->isEditable() ? Qt::Checked : Qt::Unchecked);
    m_relationsModel->setItem(row, 7, item);
}

void EntityTypeView::activated()
{
    Actions *actions = m_parent->controller()->actions();

    actions->addAttributeAction()->setEnabled(true);
    actions->addFunctionAction()->setEnabled(true);
    actions->addRelationAction()->setEnabled(true);

    QModelIndexList list1 = ui->treeViewAttributes->selectionModel()->selectedIndexes();
    QModelIndexList list2 = ui->treeViewFunctions->selectionModel()->selectedIndexes();
    QModelIndexList list3 = ui->treeViewRelations->selectionModel()->selectedIndexes();
    actions->editAttributeAction()->setEnabled(!list1.isEmpty());
    actions->editFunctionAction()->setEnabled(!list2.isEmpty());
    actions->editRelationAction()->setEnabled(!list3.isEmpty());
}

void EntityTypeView::addAttribute()
{
    on_pushButtonAddAttribute_clicked();
}

void EntityTypeView::addFunction()
{
    on_pushButtonAddFunction_clicked();
}

void EntityTypeView::addRelation()
{
    on_pushButtonAddRelation_clicked();
}

void EntityTypeView::editAttribute()
{
    on_pushButtonEditAttribute_clicked();
}

void EntityTypeView::editFunction()
{
    on_pushButtonEditFunction_clicked();
}

void EntityTypeView::editRelation()
{
    on_pushButtonEditRelation_clicked();
}

void EntityTypeView::refreshContents()
{
    QModelIndexList list1 = ui->treeViewAttributes->selectionModel()->selectedIndexes();
    QModelIndexList list2 = ui->treeViewFunctions->selectionModel()->selectedIndexes();
    QModelIndexList list3 = ui->treeViewRelations->selectionModel()->selectedIndexes();

    setEntityType(m_entityType);

    foreach(QModelIndex index, list1)
        ui->treeViewAttributes->selectionModel()->select(index, QItemSelectionModel::Select);
    foreach(QModelIndex index, list2)
        ui->treeViewFunctions->selectionModel()->select(index, QItemSelectionModel::Select);
    foreach(QModelIndex index, list3)
        ui->treeViewRelations->selectionModel()->select(index, QItemSelectionModel::Select);
}

void EntityTypeView::on_pushButtonEditAttribute_clicked()
{
    if(ui->treeViewAttributes->selectionModel()->selectedRows(0).isEmpty())
        return;

    QStandardItem *item = m_attributesModel->itemFromIndex(ui->treeViewAttributes->selectionModel()->selectedRows(0).at(0));
    LBDatabase::Attribute *attribute = item->data().value<LBDatabase::Attribute *>();

    AttributeEditor *editor = new AttributeEditor(m_entityType, this);
    editor->setAttribute(attribute);
    editor->open();
    connect(editor, SIGNAL(finished(int)), this, SLOT(refreshContents()));
}

void EntityTypeView::on_pushButtonAddAttribute_clicked()
{
    AttributeEditor *editor = new AttributeEditor(m_entityType, this);
    editor->open();
    connect(editor, SIGNAL(finished(int)), this, SLOT(refreshContents()));
}

void EntityTypeView::on_pushButtonRemoveAttribute_clicked()
{
    if(ui->treeViewAttributes->selectionModel()->selectedRows(0).isEmpty())
        return;

    QStandardItem *item = m_attributesModel->itemFromIndex(ui->treeViewAttributes->selectionModel()->selectedRows(0).at(0));
    LBDatabase::Attribute *attribute = item->data().value<LBDatabase::Attribute *>();

    QMessageBox msgBox(this);
    msgBox.setText(tr("Do you really want to delete the attribute \"%1\"?").arg(attribute->identifier()));

    if(!attribute->isCalculated())
        msgBox.setInformativeText("Note: The column of the attribute and its contents will not be deleted and may pollute the underlying database.");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setWindowModality(Qt::WindowModal);
    msgBox.setWindowFlags(Qt::Drawer);
    int ret = msgBox.exec();

    switch (ret) {
        case QMessageBox::Yes:
            attribute->entityType()->removeAttribute(attribute);
            break;
        case QMessageBox::No:
            // Don't Save was clicked
            break;
        default:
            // should never be reached
            break;
    }
    refreshContents();
}

void EntityTypeView::on_pushButtonEditFunction_clicked()
{
    if(ui->treeViewFunctions->selectionModel()->selectedRows(0).isEmpty())
        return;

    QStandardItem *item = m_functionsModel->itemFromIndex(ui->treeViewFunctions->selectionModel()->selectedRows(0).at(0));
    LBDatabase::Function *function = item->data().value<LBDatabase::Function *>();

    FunctionEditor *editor = new FunctionEditor(m_entityType, this);
    editor->setFunction(function);
    editor->open();
    connect(editor, SIGNAL(finished(int)), this, SLOT(refreshContents()));
}

void EntityTypeView::on_pushButtonAddFunction_clicked()
{
    FunctionEditor *editor = new FunctionEditor(m_entityType, this);
    editor->open();
    connect(editor, SIGNAL(finished(int)), this, SLOT(refreshContents()));
}

void EntityTypeView::on_pushButtonEditRelation_clicked()
{
    if(ui->treeViewRelations->selectionModel()->selectedRows(0).isEmpty())
        return;

    QStandardItem *item = m_relationsModel->itemFromIndex(ui->treeViewRelations->selectionModel()->selectedRows(0).at(0));
    LBDatabase::Relation *relation = item->data().value<LBDatabase::Relation *>();

    RelationEditor *editor = new RelationEditor(m_entityType, this);
    editor->setRelation(relation);
    editor->open();
    connect(editor, SIGNAL(finished(int)), this, SLOT(refreshContents()));
}

void EntityTypeView::on_pushButtonAddRelation_clicked()
{
    RelationEditor *editor = new RelationEditor(m_entityType, this);
    editor->open();
    connect(editor, SIGNAL(finished(int)), this, SLOT(refreshContents()));
}

void EntityTypeView::attributeSelectionChanged(const QModelIndex & current, const QModelIndex & previous)
{
    Q_UNUSED(previous)
    ui->pushButtonEditAttribute->setEnabled(current.isValid());
    ui->pushButtonRemoveAttribute->setEnabled(current.isValid());
    Actions *actions = m_parent->controller()->actions();
    actions->editAttributeAction()->setEnabled(current.isValid());
}

void EntityTypeView::functionSelectionChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous)
    ui->pushButtonEditFunction->setEnabled(current.isValid());
    //ui->pushButtonEditFunction->setEnabled(current.isValid());
    Actions *actions = m_parent->controller()->actions();
    actions->editFunctionAction()->setEnabled(current.isValid());
}

void EntityTypeView::relationSelectionChanged(const QModelIndex & current, const QModelIndex & previous)
{
    Q_UNUSED(previous)
    ui->pushButtonEditRelation->setEnabled(current.isValid());
    //ui->pushButtonRemoveAttribute->setEnabled(current.isValid());
    Actions *actions = m_parent->controller()->actions();
    actions->editRelationAction()->setEnabled(current.isValid());
}

void EntityTypeView::on_treeViewAttributes_doubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index)
    on_pushButtonEditAttribute_clicked();
}

void EntityTypeView::on_treeViewFunctions_doubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index)
    on_pushButtonEditFunction_clicked();
}

void EntityTypeView::on_treeViewRelations_doubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index)
    on_pushButtonEditRelation_clicked();
}

} // namespace MainWindowNS



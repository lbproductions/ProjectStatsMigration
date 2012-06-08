#include "entitytypeview.h"
#include "ui_entitytypeview.h"

#include "attributeeditor.h"
#include "functioneditor.h"

#include <LBDatabase/LBDatabase.h>

#include <QStandardItemModel>
#include <QMessageBox>

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
        itemName->setData(QVariant::fromValue<LBDatabase::Function *>(function));
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

    connect(ui->treeViewAttributes->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(attributeSelectionChanged(QModelIndex,QModelIndex)));
    connect(ui->treeViewFunctions->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(functionSelectionChanged(QModelIndex,QModelIndex)));
}

void EntityTypeView::refreshContents()
{
    QModelIndexList list1 = ui->treeViewAttributes->selectionModel()->selectedIndexes();
    QModelIndexList list2 = ui->treeViewFunctions->selectionModel()->selectedIndexes();

    setEntityType(m_entityType);

    foreach(QModelIndex index, list1)
        ui->treeViewAttributes->selectionModel()->select(index, QItemSelectionModel::Select);
    foreach(QModelIndex index, list2)
        ui->treeViewFunctions->selectionModel()->select(index, QItemSelectionModel::Select);
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

void EntityTypeView::attributeSelectionChanged(const QModelIndex & current, const QModelIndex & previous)
{
    Q_UNUSED(previous)
    ui->pushButtonEditAttribute->setEnabled(current.isValid());
    ui->pushButtonRemoveAttribute->setEnabled(current.isValid());
}

void EntityTypeView::functionSelectionChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous)
    ui->pushButtonEditFunction->setEnabled(current.isValid());
    //ui->pushButtonEditFunction->setEnabled(current.isValid());
}

} // namespace MainWindowNS



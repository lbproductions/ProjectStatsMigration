#include "relationseditor.h"
#include "ui_relationseditor.h"

#include <LBDatabase/LBDatabase.h>

#include <QPushButton>

namespace MainWindowNS {

RelationEditor::RelationEditor(LBDatabase::EntityType *entityType, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RelationsEditor),
    m_relation(0),
    m_entityType(entityType)
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);
    QDialog::setAttribute(Qt::WA_DeleteOnClose, true);
    QDialog::setWindowFlags(Qt::Drawer);

    foreach(LBDatabase::EntityType *e, entityType->context()->storage()->entityTypes())
        ui->comboBoxEntityType->addItem(e->identifier(), e->id());
    ui->comboBoxEntityType->setCurrentIndex(0);

    m_pushButtonShowTranspose = new QPushButton(tr("Show transpose"));
    connect(m_pushButtonShowTranspose, SIGNAL(clicked()), this, SLOT(showTransposeRelation()));
    ui->buttonBox->addButton(m_pushButtonShowTranspose, QDialogButtonBox::ActionRole);
    m_pushButtonShowTranspose->setEnabled(false);
    ui->buttonBox->button( QDialogButtonBox::Save )->setEnabled(false);

    connect(ui->checkBoxEditable, SIGNAL(stateChanged(int)), this, SLOT(checkCheckboxStates()));
    connect(ui->checkBoxCalculated, SIGNAL(stateChanged(int)), this, SLOT(checkCheckboxStates()));
    connect(ui->comboBoxCardinality, SIGNAL(currentIndexChanged(int)), this, SLOT(checkCheckboxStates()));
    connect(ui->comboBoxDirection, SIGNAL(currentIndexChanged(int)), this, SLOT(checkCheckboxStates()));
    connect(ui->comboBoxEntityType, SIGNAL(currentIndexChanged(int)), this, SLOT(checkCheckboxStates()));

    connect(ui->lineEditTableName, SIGNAL(textChanged(QString)), this, SLOT(checkLineEditContents()));
    connect(ui->lineEditIdentifier, SIGNAL(textChanged(QString)), this, SLOT(checkLineEditContents()));
    connect(ui->lineEditEntityIdColumnName, SIGNAL(textChanged(QString)), this, SLOT(checkLineEditContents()));
    connect(ui->lineEditEntityIdRightColumnName, SIGNAL(textChanged(QString)), this, SLOT(checkLineEditContents()));
    connect(ui->lineEditDisplayNameRight, SIGNAL(textChanged(QString)), this, SLOT(checkLineEditContents()));
    connect(ui->lineEditIdentifierRight, SIGNAL(textChanged(QString)), this, SLOT(checkLineEditContents()));

    checkCheckboxStates();
}

RelationEditor::~RelationEditor()
{
    delete ui;
}

void RelationEditor::setRelation(LBDatabase::Relation *relation)
{
    m_relation = relation;
    ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(true);
    ui->labelId->setText(QString::number(relation->id()));
    ui->lineEditIdentifier->setEnabled(relation->isCalculated());
    ui->lineEditIdentifier->setText(relation->identifier());
    ui->lineEditDisplayName->setText(relation->displayName());
    for(int i = 0; i < ui->comboBoxEntityType->count(); ++i) {
        if(ui->comboBoxEntityType->itemData(i).toInt() == relation->entityType()->id()) {
            ui->comboBoxEntityType->setCurrentIndex(i);
            break;
        }
    }
    ui->comboBoxEntityType->setEnabled(relation->isCalculated());
    ui->comboBoxCardinality->setCurrentIndex(static_cast<int>(relation->cardinality()));
    ui->comboBoxCardinality->setEnabled(relation->isCalculated());
    ui->comboBoxDirection->setCurrentIndex(static_cast<int>(relation->direction()));

    ui->checkBoxEditable->setChecked(relation->isEditable());
    ui->checkBoxCalculated->setChecked(relation->isCalculated());
    ui->checkBoxCalculated->setEnabled(false);

    ui->lineEditTableName->setText(relation->tableName());
    ui->lineEditEntityIdColumnName->setText(relation->leftEntityIdColumnName());
    ui->lineEditEntityIdRightColumnName->setText(relation->rightEntityIdColumnName());

    ui->lineEditTableName->setEnabled(false);
    ui->lineEditEntityIdColumnName->setEnabled(false);
    ui->lineEditEntityIdRightColumnName->setEnabled(false);
    m_pushButtonShowTranspose->setEnabled(relation->transposeRelation());

    if(relation->transposeRelation()) {
        ui->lineEditDisplayNameRight->setText(relation->transposeRelation()->displayName());
        ui->lineEditIdentifierRight->setText(relation->transposeRelation()->identifier());
    }

    if(relation->isTranspose()) {
        ui->lineEditDisplayName->setEnabled(false);
        ui->lineEditIdentifier->setEnabled(false);
        ui->comboBoxEntityType->setEnabled(false);
        ui->comboBoxCardinality->setEnabled(false);
        ui->comboBoxDirection->setEnabled(false);
        ui->checkBoxEditable->setEnabled(false);
        ui->checkBoxCalculated->setEnabled(false);
        ui->lineEditTableName->setEnabled(false);
        ui->lineEditEntityIdColumnName->setEnabled(false);
        ui->lineEditEntityIdRightColumnName->setEnabled(false);
        ui->lineEditDisplayNameRight->setEnabled(false);
        ui->lineEditIdentifierRight->setEnabled(false);

        ui->buttonBox->setStandardButtons(QDialogButtonBox::Ok);
    }
}

void RelationEditor::checkCheckboxStates()
{
    ui->checkBoxCalculated->setEnabled(!ui->checkBoxEditable->isChecked() && !m_relation);
    ui->checkBoxEditable->setEnabled(!ui->checkBoxCalculated->isChecked());

    ui->groupBoxAdvanced->setEnabled(!ui->checkBoxCalculated->isChecked());

    if(static_cast<LBDatabase::Relation::Direction>(ui->comboBoxDirection->currentIndex()) == LBDatabase::Relation::LeftToRight) {
        ui->groupBoxTransposeRelation->setEnabled(false);
        ui->lineEditDisplayNameRight->setText(QString());
        ui->lineEditIdentifierRight->setText(QString());
    }
    else {
        ui->groupBoxTransposeRelation->setEnabled(true);
        if(m_relation && m_relation->transposeRelation()) {
            ui->lineEditDisplayNameRight->setText(m_relation->transposeRelation()->displayName());
            ui->lineEditIdentifierRight->setText(m_relation->transposeRelation()->identifier());
        }
        else {
            LBDatabase::EntityType *relatedEntityType = m_entityType->context()->storage()->entityType(ui->comboBoxEntityType->itemData(ui->comboBoxEntityType->currentIndex()).toInt());

            QString name = relatedEntityType->identifier();
            ui->lineEditDisplayNameRight->setText(name);
            ui->lineEditIdentifierRight->setText(name);
        }
    }

    if(ui->checkBoxCalculated->isChecked()) {
        ui->lineEditTableName->setText(QString());
        ui->lineEditEntityIdColumnName->setText(QString());
        ui->lineEditEntityIdRightColumnName->setText(QString());
    }
    else {
        if(!m_relation) {
            if(static_cast<LBDatabase::Relation::Cardinality>(ui->comboBoxCardinality->currentIndex()) != LBDatabase::Relation::ManyToMany) {
                LBDatabase::EntityType *relatedEntityType = m_entityType->context()->storage()->entityType(ui->comboBoxEntityType->itemData(ui->comboBoxEntityType->currentIndex()).toInt());

                ui->lineEditTableName->setText(relatedEntityType->context()->tableName());
                ui->lineEditEntityIdRightColumnName->setText("id");

                QString name = m_entityType->identifier();
                if(relatedEntityType == m_entityType) {
                    name.prepend(QLatin1String("related"));
                }

                ui->lineEditEntityIdColumnName->setText(name);
            }
            else {
                ui->lineEditTableName->setText(ui->lineEditIdentifier->text()+"s");
                ui->lineEditEntityIdColumnName->setText(m_entityType->identifier());

                LBDatabase::EntityType *relatedEntityType = m_entityType->context()->storage()->entityType(ui->comboBoxEntityType->itemData(ui->comboBoxEntityType->currentIndex()).toInt());

                QString name = relatedEntityType->identifier();
                if(relatedEntityType == m_entityType) {
                    name.prepend(QLatin1String("related"));
                }

                ui->lineEditEntityIdRightColumnName->setText(name);
            }
        }
    }
}

void RelationEditor::checkLineEditContents()
{
    bool enable = true;
    foreach(LBDatabase::Relation *relation, m_entityType->relations()) {
        if(relation != m_relation &&
                QString::compare(relation->identifier(),ui->lineEditIdentifier->text(),Qt::CaseInsensitive) == 0
                )
            enable = false;
    }
    ui->buttonBox->button( QDialogButtonBox::Save )->setEnabled(
                !ui->lineEditIdentifier->text().isEmpty() &&
                enable &&
                (
                ui->checkBoxCalculated->isChecked() ||
                !ui->lineEditTableName->text().isEmpty() &&
                !ui->lineEditTableName->text().startsWith("lbmeta_") &&
                !ui->lineEditEntityIdColumnName->text().isEmpty() &&
                !ui->lineEditEntityIdRightColumnName->text().isEmpty() &&
                 (static_cast<LBDatabase::Relation::Direction>(ui->comboBoxDirection->currentIndex()) == LBDatabase::Relation::LeftToRight ||
                !ui->lineEditDisplayNameRight->text().isEmpty() &&
                !ui->lineEditIdentifierRight->text().isEmpty())
                 )
                );
}

void RelationEditor::showTransposeRelation()
{
    RelationEditor *editor = new RelationEditor(m_entityType, this);
    editor->setRelation(m_relation->transposeRelation());
    editor->open();
}

} // namespace MainWindowNS

void MainWindowNS::RelationEditor::on_buttonBox_accepted()
{
    if(!m_relation) {
        LBDatabase::RelationMetaData metaData;
        metaData.identifier = ui->lineEditIdentifier->text();
        metaData.identifierRight = ui->lineEditIdentifierRight->text();
        metaData.displayName = ui->lineEditDisplayName->text();
        metaData.displayNameRight = ui->lineEditDisplayNameRight->text();
        metaData.cardinality = static_cast<LBDatabase::Relation::Cardinality>(ui->comboBoxCardinality->currentIndex());
        metaData.direction = static_cast<LBDatabase::Relation::Direction>(ui->comboBoxDirection->currentIndex());
        metaData.editable = ui->checkBoxEditable->isChecked();
        metaData.calculated = ui->checkBoxCalculated->isChecked();
        metaData.entityTypeId = m_entityType->id();
        LBDatabase::EntityType *relatedEntityType = m_entityType->context()->storage()->entityType(ui->comboBoxEntityType->itemData(ui->comboBoxEntityType->currentIndex()).toInt());
        metaData.entityTypeOtherId = relatedEntityType->id();
        metaData.leftEntityIdColumnName = ui->lineEditEntityIdColumnName->text();
        metaData.rightEntityIdColumnName = ui->lineEditEntityIdRightColumnName->text();
        metaData.tableName = ui->lineEditTableName->text();
        m_relation = m_entityType->addRelation(metaData);
    }
    else {
//        m_attribute->setDisplayName(ui->lineEditDisplayName->text());
//        m_attribute->setIdentifier(ui->lineEditIdentifier->text());
//        m_attribute->setType(LBDatabase::Attribute::typeNameToType(ui->comboBoxType->currentText()));
//        m_attribute->setEditable(ui->checkBoxEditable->isChecked());
//        m_attribute->setCalculated(ui->checkBoxCalculated->isChecked());
//        m_attribute->setCached(ui->checkBoxCached->isChecked());
//        m_attribute->setDefaultValue(ui->lineEditDefaultValue->text());
    }
    emit finished(QDialog::Accepted);
}

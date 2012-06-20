#include "dependencyeditor.h"
#include "ui_dependencyeditor.h"

#include <LBDatabase/LBDatabase.h>

#include <QPushButton>

namespace MainWindowNS {

DependencyEditor::DependencyEditor(LBDatabase::EntityType *entityType, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DependencyEditor),
    m_entityType(entityType)
{
    ui->setupUi(this);

    foreach(LBDatabase::Property *p, entityType->properties()) {
        if(p->isCalculated())
            ui->comboBoxProperty->addItem(p->identifier(), QVariant::fromValue<LBDatabase::Property *>(p));
    }

    ui->comboBoxRelation->addItem(tr("Self"), -1);

    foreach(LBDatabase::EntityType *type, entityType->context()->storage()->entityTypes()) {
        ui->comboBoxRelation->addItem(tr("All %1").arg(type->displayNamePlural()), QVariant::fromValue<LBDatabase::EntityType *>(type));
    }
    foreach(LBDatabase::Relation *relation, entityType->relations()) {
        ui->comboBoxRelation->addItem(tr("All %1 in %2").arg(relation->entityTypeOther()->displayNamePlural()).arg(relation->identifier()), QVariant::fromValue<LBDatabase::Relation *>(relation));
    }

    connect(ui->comboBoxRelation, SIGNAL(currentIndexChanged(int)), this, SLOT(relationChanged(int)));

    ui->comboBoxRelation->setCurrentIndex(0);
    relationChanged(0);

    m_metaData.id = -1;

    connect(ui->buttonBox->button(QDialogButtonBox::Save), SIGNAL(clicked()), this, SLOT(save()));
}

DependencyEditor::~DependencyEditor()
{
    delete ui;
}

void DependencyEditor::setDependencyMetaData(const LBDatabase::DependencyMetaData &metaData)
{
}

void DependencyEditor::relationChanged(int index)
{
    if(index == 0) {
        ui->comboBoxDependency->clear();
        foreach(LBDatabase::Property *p, m_entityType->properties()) {
            ui->comboBoxDependency->addItem(p->identifier(), QVariant::fromValue<LBDatabase::Property *>(p));
        }
    }
    else if(index <= m_entityType->context()->storage()->entityTypes().size()) {
        ui->comboBoxDependency->clear();
        LBDatabase::EntityType *type = ui->comboBoxRelation->itemData(index).value<LBDatabase::EntityType *>();
        foreach(LBDatabase::Property *p, type->properties()) {
            ui->comboBoxDependency->addItem(p->identifier(), QVariant::fromValue<LBDatabase::Property *>(p));
        }
    }
    else {
        ui->comboBoxDependency->clear();
        LBDatabase::Relation *relation = ui->comboBoxRelation->itemData(index).value<LBDatabase::Relation *>();
        LBDatabase::EntityType *type = relation->entityTypeOther();
        if(!m_entityType->properties().contains(relation) && relation->transposeRelation())
            type = relation->transposeRelation()->entityTypeOther();
        foreach(LBDatabase::Property *p, type->properties()) {
            ui->comboBoxDependency->addItem(p->identifier(), QVariant::fromValue<LBDatabase::Property *>(p));
        }
    }
    ui->comboBoxDependency->setCurrentIndex(0);
}

void DependencyEditor::save()
{
    LBDatabase::Property *dependency = ui->comboBoxDependency->itemData(ui->comboBoxDependency->currentIndex()).value<LBDatabase::Property *>();
    m_metaData.dependencyPropertyId = dependency->id();
    m_metaData.dependencyPropertyType = dependency->propertyType();

    LBDatabase::Property *dependend = ui->comboBoxProperty->itemData(ui->comboBoxProperty->currentIndex()).value<LBDatabase::Property *>();
    m_metaData.dependendPropertyId = dependend->id();
    m_metaData.dependendPropertyType = dependend->propertyType();

    int index = ui->comboBoxRelation->currentIndex();
    if(index == 0) {
        m_metaData.entityRelation = -1;
    }
    else if(index <= m_entityType->context()->storage()->entityTypes().size()) {
        m_metaData.entityRelation = 0;
    }
    else {
        LBDatabase::Relation *relation = ui->comboBoxRelation->itemData(index).value<LBDatabase::Relation *>();
        m_metaData.entityRelation = relation->id();
    }

    if(m_metaData.id == -1) {
        m_entityType->context()->storage()->driver()->addDependency(m_metaData);
    }
    else {
        //TODO: dependency editieren
    }

    accept();
}

} // namespace MainWindowNS

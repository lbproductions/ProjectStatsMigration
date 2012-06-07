#include "attributeeditor.h"
#include "ui_attributeeditor.h"

#include <LBDatabase/LBDatabase.h>

namespace MainWindowNS {

AttributeEditor::AttributeEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AttributeEditor)
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);
    QDialog::setAttribute(Qt::WA_DeleteOnClose, true);

    connect(ui->checkBoxEditable, SIGNAL(stateChanged(int)), this, SLOT(checkCheckboxStates()));
    connect(ui->checkBoxCalculated, SIGNAL(stateChanged(int)), this, SLOT(checkCheckboxStates()));
}

AttributeEditor::~AttributeEditor()
{
    delete ui;
}

void AttributeEditor::setAttribute(LBDatabase::Attribute *attribute)
{
    m_attribute = attribute;
    ui->labelId->setText(QString::number(attribute->id()));
    ui->lineEditIdentifier->setText(attribute->identifier());
    ui->lineEditDisplayName->setText(attribute->displayName());
    ui->comboBoxType->addItems(LBDatabase::Attribute::typeNames());
    ui->comboBoxType->setCurrentIndex(LBDatabase::Attribute::typeNames().indexOf(attribute->Attribute::typeName()));
    ui->checkBoxEditable->setChecked(attribute->isEditable());
    ui->checkBoxCalculated->setChecked(attribute->isCalculated());
    ui->checkBoxCached->setChecked(attribute->isCached());
}

} // namespace MainWindowNS

void MainWindowNS::AttributeEditor::on_buttonBox_accepted()
{
    m_attribute->setDisplayName(ui->lineEditDisplayName->text());
    m_attribute->setIdentifier(ui->lineEditIdentifier->text());
    m_attribute->setType(LBDatabase::Attribute::typeNameToType(ui->comboBoxType->currentText()));
    m_attribute->setEditable(ui->checkBoxEditable->isChecked());
    m_attribute->setCalculated(ui->checkBoxCalculated->isChecked());
    m_attribute->setCached(ui->checkBoxCached->isChecked());
}

void MainWindowNS::AttributeEditor::checkCheckboxStates()
{
    ui->checkBoxCalculated->setEnabled(!ui->checkBoxEditable->isChecked());
    ui->checkBoxEditable->setEnabled(!ui->checkBoxCalculated->isChecked());
}

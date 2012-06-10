#include "attributeeditor.h"
#include "ui_attributeeditor.h"

#include <LBDatabase/LBDatabase.h>

#include <QPushButton>

namespace MainWindowNS {

AttributeEditor::AttributeEditor(LBDatabase::EntityType *entityType, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AttributeEditor),
    m_attribute(0),
    m_entityType(entityType)
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);
    QDialog::setAttribute(Qt::WA_DeleteOnClose, true);
    QDialog::setWindowFlags(Qt::Drawer);

    ui->buttonBox->button( QDialogButtonBox::Save )->setEnabled(false);

    ui->comboBoxType->addItems(LBDatabase::Attribute::typeNames());
    ui->comboBoxType->setCurrentIndex(0);

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
    ui->lineEditIdentifier->setEnabled(attribute->isCalculated());
    ui->labelId->setText(QString::number(attribute->id()));
    ui->lineEditIdentifier->setText(attribute->identifier());
    ui->lineEditDisplayName->setText(attribute->displayName());
    ui->comboBoxType->setCurrentIndex(static_cast<int>(attribute->type()));
    ui->checkBoxEditable->setChecked(attribute->isEditable());
    ui->checkBoxCalculated->setChecked(attribute->isCalculated());
    ui->checkBoxCached->setChecked(attribute->isCached());
    if(!attribute->isCalculated())
        ui->lineEditColumnName->setText(attribute->identifier());
    ui->lineEditDefaultValue->setText(attribute->defaultValue().toString());
    ui->checkBoxCalculated->setEnabled(false);
}

void AttributeEditor::on_buttonBox_accepted()
{
    if(!m_attribute) {
        LBDatabase::AttributeMetaData metaData;
        metaData.identifier = ui->lineEditIdentifier->text();
        metaData.displayName = ui->lineEditDisplayName->text();
        metaData.type = LBDatabase::Attribute::typeNameToType(ui->comboBoxType->currentText());
        metaData.editable = ui->checkBoxEditable->isChecked();
        metaData.calculated = ui->checkBoxCalculated->isChecked();
        metaData.cached = ui->checkBoxCached->isChecked();
        metaData.defaultValue = ui->lineEditDefaultValue->text();
        m_attribute = m_entityType->addAttribute(metaData);
    }
    else {
        m_attribute->setDisplayName(ui->lineEditDisplayName->text());
        m_attribute->setIdentifier(ui->lineEditIdentifier->text());
        m_attribute->setType(LBDatabase::Attribute::typeNameToType(ui->comboBoxType->currentText()));
        m_attribute->setEditable(ui->checkBoxEditable->isChecked());
        m_attribute->setCalculated(ui->checkBoxCalculated->isChecked());
        m_attribute->setCached(ui->checkBoxCached->isChecked());
        m_attribute->setDefaultValue(ui->lineEditDefaultValue->text());
    }
    emit finished(QDialog::Accepted);
}

void AttributeEditor::checkCheckboxStates()
{
    ui->checkBoxCalculated->setEnabled(!ui->checkBoxEditable->isChecked() && !m_attribute);
    ui->checkBoxEditable->setEnabled(!ui->checkBoxCalculated->isChecked());

    ui->groupBoxAdvanced->setEnabled(!ui->checkBoxCalculated->isChecked());
    ui->lineEditDefaultValue->setEnabled(!ui->checkBoxCalculated->isChecked());

    if(ui->checkBoxCalculated->isChecked()) {
        ui->lineEditColumnName->setText(QString());
    }
    else {
        ui->lineEditColumnName->setText(ui->lineEditIdentifier->text());
    }
}

void AttributeEditor::on_lineEditIdentifier_textChanged(const QString &text)
{
    bool enable = true;
    foreach(LBDatabase::Attribute *attribute, m_entityType->attributes()) {
        if(attribute != m_attribute && QString::compare(attribute->identifier(),text,Qt::CaseInsensitive) == 0)
            enable = false;
    }

    if(ui->checkBoxCalculated->isChecked() || (m_attribute && m_attribute->isCalculated())) {
        ui->lineEditColumnName->setText(QString());
    }
    else {
        ui->lineEditColumnName->setText(text);
    }

    ui->buttonBox->button( QDialogButtonBox::Save )->setEnabled(enable && !text.isEmpty());
}

} // namespace MainWindowNS





void MainWindowNS::AttributeEditor::on_buttonBox_rejected()
{
    emit finished(QDialog::Rejected);
}

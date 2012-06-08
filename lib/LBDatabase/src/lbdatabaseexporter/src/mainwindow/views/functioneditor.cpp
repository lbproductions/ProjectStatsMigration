#include "functioneditor.h"
#include "ui_functioneditor.h"

#include <LBDatabase/LBDatabase.h>

#include <QPushButton>

namespace MainWindowNS {

FunctionEditor::FunctionEditor(LBDatabase::EntityType *entityType, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FunctionEditor),
    m_function(0),
    m_entityType(entityType)
{
    ui->setupUi(this);

    setWindowModality(Qt::WindowModal);
    QDialog::setAttribute(Qt::WA_DeleteOnClose, true);
    QDialog::setWindowFlags(Qt::Drawer);

    foreach(LBDatabase::EntityType *e, entityType->context()->storage()->entityTypes())
        ui->comboBoxKeyEntityType->addItem(e->identifier(), e->id());
    ui->comboBoxKeyEntityType->setCurrentIndex(0);

    ui->comboBoxType->addItems(LBDatabase::Attribute::typeNames());
    ui->comboBoxType->setCurrentIndex(0);
    ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(false);

    ui->lineEditEntityIdColumnName->setText(entityType->identifier());

    connect(ui->checkBoxEditable, SIGNAL(stateChanged(int)), this, SLOT(checkCheckboxStates()));
    connect(ui->checkBoxCalculated, SIGNAL(stateChanged(int)), this, SLOT(checkCheckboxStates()));

    connect(ui->lineEditTableName, SIGNAL(textChanged(QString)), this, SLOT(checkLineEditContents()));
    connect(ui->lineEditEntityIdColumnName, SIGNAL(textChanged(QString)), this, SLOT(checkLineEditContents()));
    connect(ui->lineEditKeyEntityIdColumnName, SIGNAL(textChanged(QString)), this, SLOT(checkLineEditContents()));
    connect(ui->lineEditValueColumnName, SIGNAL(textChanged(QString)), this, SLOT(checkLineEditContents()));
}

FunctionEditor::~FunctionEditor()
{
    delete ui;
}

void FunctionEditor::setFunction(LBDatabase::Function *function)
{
    m_function = function;
    ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(true);
    ui->labelId->setText(QString::number(function->id()));
    ui->lineEditIdentifier->setEnabled(function->isCalculated());
    ui->lineEditIdentifier->setText(function->identifier());
    ui->lineEditDisplayName->setText(function->displayName());
    for(int i = 0; i < ui->comboBoxKeyEntityType->count(); ++i) {
        if(ui->comboBoxKeyEntityType->itemData(i).toInt() == function->keyEntityType()->id()) {
            ui->comboBoxKeyEntityType->setCurrentIndex(i);
            break;
        }
    }
    ui->comboBoxKeyEntityType->setEnabled(function->isCalculated());
    ui->comboBoxType->setCurrentIndex(function->type());
    ui->checkBoxEditable->setChecked(function->isEditable());
    ui->checkBoxCalculated->setChecked(function->isCalculated());
    ui->checkBoxCalculated->setEnabled(false);

    ui->lineEditTableName->setText(function->tableName());
    ui->lineEditEntityIdColumnName->setText(function->entityColumnName());
    ui->lineEditKeyEntityIdColumnName->setText(function->keyEntityColumnName());
    ui->lineEditValueColumnName->setText(function->valueColumnName());

    ui->lineEditTableName->setEnabled(false);
    ui->lineEditEntityIdColumnName->setEnabled(false);
    ui->lineEditKeyEntityIdColumnName->setEnabled(false);
    ui->lineEditValueColumnName->setEnabled(false);
}

} // namespace MainWindowNS

void MainWindowNS::FunctionEditor::on_buttonBox_accepted()
{
    if(!m_function) {
        LBDatabase::FunctionMetaData metaData;
        metaData.identifier = ui->lineEditIdentifier->text();
        metaData.displayName = ui->lineEditDisplayName->text();
        metaData.type = LBDatabase::Attribute::typeNameToType(ui->comboBoxType->currentText());
        metaData.editable = ui->checkBoxEditable->isChecked();
        metaData.calculated = ui->checkBoxCalculated->isChecked();
        metaData.cached = true;

        metaData.keyEntityTypeId = ui->comboBoxKeyEntityType->itemData(ui->comboBoxKeyEntityType->currentIndex()).toInt();
        metaData.tableName = ui->lineEditTableName->text();
        metaData.entityColumnName = ui->lineEditEntityIdColumnName->text();
        metaData.keyEntityColumnName = ui->lineEditKeyEntityIdColumnName->text();
        metaData.valueColumnName = ui->lineEditValueColumnName->text();
        m_function = m_entityType->addFunction(metaData);
    }
    else {
        m_function->setEditable(ui->checkBoxEditable->isChecked());
        m_function->setDisplayName(ui->lineEditDisplayName->text());
        m_function->setIdentifier(ui->lineEditIdentifier->text());
        m_function->setType(static_cast<LBDatabase::Attribute::Type>(ui->comboBoxType->currentIndex()));
        LBDatabase::EntityType *keyEntityType = m_entityType->context()->storage()->entityType(ui->comboBoxKeyEntityType->itemData(ui->comboBoxKeyEntityType->currentIndex()).toInt());
        m_function->setKeyEntityType(keyEntityType);
    }
    emit finished(QDialog::Accepted);
}

void MainWindowNS::FunctionEditor::checkCheckboxStates()
{
    ui->checkBoxCalculated->setEnabled(!ui->checkBoxEditable->isChecked() && !m_function);
    ui->checkBoxEditable->setEnabled(!ui->checkBoxCalculated->isChecked());

    ui->groupBoxAdvanced->setEnabled(!ui->checkBoxCalculated->isChecked());

    if(ui->checkBoxCalculated->isChecked()) {
        ui->lineEditTableName->setText(QString());
        ui->lineEditValueColumnName->setText(QString());
        ui->lineEditEntityIdColumnName->setText(QString());
        ui->lineEditKeyEntityIdColumnName->setText(QString());
    }
    else {
        ui->lineEditTableName->setText(ui->lineEditIdentifier->text()+"s");
        ui->lineEditValueColumnName->setText(ui->lineEditIdentifier->text());
        ui->lineEditEntityIdColumnName->setText(m_entityType->identifier());

        LBDatabase::EntityType *keyEntityType = m_entityType->context()->storage()->entityType(ui->comboBoxKeyEntityType->itemData(ui->comboBoxKeyEntityType->currentIndex()).toInt());

        QString name = keyEntityType->identifier();
        if(keyEntityType == m_entityType) {
            name.prepend(QLatin1String("key"));
        }

        ui->lineEditKeyEntityIdColumnName->setText(name);
    }
}

void MainWindowNS::FunctionEditor::checkLineEditContents()
{
    bool enable = true;
    foreach(LBDatabase::Function *function, m_entityType->functions()) {
        if(function != m_function &&
                (QString::compare(function->identifier(),ui->lineEditIdentifier->text(),Qt::CaseInsensitive) == 0 ||
                QString::compare(function->tableName(),ui->lineEditTableName->text(),Qt::CaseInsensitive) == 0)
                )
            enable = false;
    }
    ui->buttonBox->button( QDialogButtonBox::Save )->setEnabled(
                enable &&
                (ui->checkBoxCalculated->isChecked() ||
                !ui->lineEditTableName->text().isEmpty() &&
                !ui->lineEditTableName->text().startsWith("lbmeta_") &&
                !ui->lineEditEntityIdColumnName->text().isEmpty() &&
                !ui->lineEditKeyEntityIdColumnName->text().isEmpty() &&
                !ui->lineEditValueColumnName->text().isEmpty())
                );
}

void MainWindowNS::FunctionEditor::on_lineEditIdentifier_textEdited(const QString &text)
{
    bool enable = true;
    foreach(LBDatabase::Function *function, m_entityType->functions()) {
        if(function != m_function && QString::compare(function->identifier(),text,Qt::CaseInsensitive) == 0)
            enable = false;
    }

    if(ui->checkBoxCalculated->isChecked() || (m_function && m_function->isCalculated())) {
        ui->lineEditKeyEntityIdColumnName->setText(QString());
    }
    else {
        ui->lineEditTableName->setText(text+"s");
        ui->lineEditValueColumnName->setText(text);
    }

    ui->buttonBox->button( QDialogButtonBox::Save )->setEnabled(enable && !text.isEmpty());
}

void MainWindowNS::FunctionEditor::on_comboBoxKeyEntityType_currentIndexChanged(int index)
{
    if(ui->checkBoxCalculated->isChecked() || (m_function && m_function->isCalculated())) {
        ui->lineEditKeyEntityIdColumnName->setText(QString());
    }
    else {
        LBDatabase::EntityType *keyEntityType = m_entityType->context()->storage()->entityType(ui->comboBoxKeyEntityType->itemData(index).toInt());
        QString name = keyEntityType->identifier();
        if(keyEntityType == m_entityType) {
            name.prepend(QLatin1String("key"));
        }

        ui->lineEditKeyEntityIdColumnName->setText(name);
    }
}

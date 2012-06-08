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
    ui->lineEditIdentifier->setEnabled(false);
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

}

void MainWindowNS::FunctionEditor::checkCheckboxStates()
{
    ui->checkBoxCalculated->setEnabled(!ui->checkBoxEditable->isChecked() && !m_function);
    ui->checkBoxEditable->setEnabled(!ui->checkBoxCalculated->isChecked());

    ui->groupBoxAdvanced->setEnabled(!ui->checkBoxCalculated->isChecked());
}

void MainWindowNS::FunctionEditor::checkLineEditContents()
{
    ui->buttonBox->button( QDialogButtonBox::Save )->setEnabled(
                ui->checkBoxCalculated->isChecked() ||
                !ui->lineEditTableName->text().isEmpty() &&
                !ui->lineEditEntityIdColumnName->text().isEmpty() &&
                !ui->lineEditKeyEntityIdColumnName->text().isEmpty() &&
                !ui->lineEditValueColumnName->text().isEmpty()
                );
}

void MainWindowNS::FunctionEditor::on_lineEditIdentifier_textEdited(const QString &text)
{
    ui->buttonBox->button( QDialogButtonBox::Save )->setEnabled(!text.isEmpty());
    ui->lineEditTableName->setText(text+"s");
    ui->lineEditValueColumnName->setText(text);
}

void MainWindowNS::FunctionEditor::on_comboBoxKeyEntityType_currentIndexChanged(int index)
{
    if(m_function && m_function->isCalculated())
        return;

    LBDatabase::EntityType *keyEntityType = m_entityType->context()->storage()->entityType(ui->comboBoxKeyEntityType->itemData(index).toInt());
    ui->lineEditKeyEntityIdColumnName->setText(keyEntityType->identifier());
}

#include "functioneditor.h"
#include "ui_functioneditor.h"

#include <LBDatabase/LBDatabase.h>

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

    ui->comboBoxType->addItems(LBDatabase::Attribute::typeNames());
    ui->comboBoxType->setCurrentIndex(0);

    connect(ui->checkBoxEditable, SIGNAL(stateChanged(int)), this, SLOT(checkCheckboxStates()));
    connect(ui->checkBoxCalculated, SIGNAL(stateChanged(int)), this, SLOT(checkCheckboxStates()));
}

FunctionEditor::~FunctionEditor()
{
    delete ui;
}

void FunctionEditor::setFunction(LBDatabase::Function *function)
{
    m_function = function;
    ui->labelId->setText(QString::number(function->id()));
    ui->lineEditIdentifier->setText(function->identifier());
    ui->lineEditDisplayName->setText(function->displayName());
    ui->comboBoxType->setCurrentIndex(function->type());
    ui->checkBoxEditable->setChecked(function->isEditable());
    ui->checkBoxCalculated->setChecked(function->isCalculated());
}

} // namespace MainWindowNS

void MainWindowNS::FunctionEditor::on_buttonBox_accepted()
{

}

void MainWindowNS::FunctionEditor::checkCheckboxStates()
{
    ui->checkBoxCalculated->setEnabled(!ui->checkBoxEditable->isChecked());
    ui->checkBoxEditable->setEnabled(!ui->checkBoxCalculated->isChecked());
}

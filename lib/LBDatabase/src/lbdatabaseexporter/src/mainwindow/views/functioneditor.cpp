#include "functioneditor.h"
#include "ui_functioneditor.h"

namespace MainWindowNS {

FunctionEditor::FunctionEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FunctionEditor)
{
    ui->setupUi(this);
}

FunctionEditor::~FunctionEditor()
{
    delete ui;
}

} // namespace MainWindowNS

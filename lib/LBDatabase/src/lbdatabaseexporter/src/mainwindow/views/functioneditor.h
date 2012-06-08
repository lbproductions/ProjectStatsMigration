#ifndef MAINWINDOWNS_FUNCTIONEDITOR_H
#define MAINWINDOWNS_FUNCTIONEDITOR_H

#include <QDialog>

namespace LBDatabase {
class Function;
class EntityType;
}

namespace MainWindowNS {

namespace Ui {
class FunctionEditor;
}

class FunctionEditor : public QDialog
{
    Q_OBJECT
    
public:
    explicit FunctionEditor(LBDatabase::EntityType *entityType, QWidget *parent = 0);
    ~FunctionEditor();

    void setFunction(LBDatabase::Function *function);
    
private slots:
    void on_buttonBox_accepted();

    void checkCheckboxStates();

private:
    Ui::FunctionEditor *ui;
    LBDatabase::Function *m_function;
    LBDatabase::EntityType *m_entityType;
};


} // namespace MainWindowNS
#endif // MAINWINDOWNS_FUNCTIONEDITOR_H

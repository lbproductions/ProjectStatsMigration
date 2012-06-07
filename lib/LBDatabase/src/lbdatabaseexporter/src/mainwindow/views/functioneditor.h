#ifndef MAINWINDOWNS_FUNCTIONEDITOR_H
#define MAINWINDOWNS_FUNCTIONEDITOR_H

#include <QDialog>

namespace MainWindowNS {

namespace Ui {
class FunctionEditor;
}

class FunctionEditor : public QDialog
{
    Q_OBJECT
    
public:
    explicit FunctionEditor(QWidget *parent = 0);
    ~FunctionEditor();
    
private:
    Ui::FunctionEditor *ui;
};


} // namespace MainWindowNS
#endif // MAINWINDOWNS_FUNCTIONEDITOR_H

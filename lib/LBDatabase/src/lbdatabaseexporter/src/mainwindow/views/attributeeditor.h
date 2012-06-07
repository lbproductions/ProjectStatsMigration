#ifndef MAINWINDOWNS_ATTRIBUTEEDITOR_H
#define MAINWINDOWNS_ATTRIBUTEEDITOR_H

#include <QDialog>

namespace LBDatabase {
class Attribute;
}

namespace MainWindowNS {

namespace Ui {
class AttributeEditor;
}

class AttributeEditor : public QDialog
{
    Q_OBJECT
    
public:
    explicit AttributeEditor(QWidget *parent = 0);
    ~AttributeEditor();

    void setAttribute(LBDatabase::Attribute *attribute);
    
private slots:
    void on_buttonBox_accepted();
    void checkCheckboxStates();

private:
    Ui::AttributeEditor *ui;
    LBDatabase::Attribute *m_attribute;
};


} // namespace MainWindowNS
#endif // MAINWINDOWNS_ATTRIBUTEEDITOR_H

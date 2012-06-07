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
    void setNewAttribute(bool newAttribute);
    
private slots:
    void on_buttonBox_accepted();
    void checkCheckboxStates();

    void on_buttonBox_rejected();

private:
    Ui::AttributeEditor *ui;
    LBDatabase::Attribute *m_attribute;
    bool m_newAttribute;
};


} // namespace MainWindowNS
#endif // MAINWINDOWNS_ATTRIBUTEEDITOR_H

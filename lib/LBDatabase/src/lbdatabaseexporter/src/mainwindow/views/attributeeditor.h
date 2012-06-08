#ifndef MAINWINDOWNS_ATTRIBUTEEDITOR_H
#define MAINWINDOWNS_ATTRIBUTEEDITOR_H

#include <QDialog>

namespace LBDatabase {
class Attribute;
class EntityType;
}

namespace MainWindowNS {

namespace Ui {
class AttributeEditor;
}

class AttributeEditor : public QDialog
{
    Q_OBJECT
    
public:
    explicit AttributeEditor(LBDatabase::EntityType *entityType, QWidget *parent = 0);
    ~AttributeEditor();

    void setAttribute(LBDatabase::Attribute *attribute);
    
private slots:
    void on_buttonBox_accepted();
    void checkCheckboxStates();

    void on_lineEditIdentifier_textChanged(const QString &arg1);

    void on_buttonBox_rejected();

private:
    Ui::AttributeEditor *ui;
    LBDatabase::Attribute *m_attribute;
    LBDatabase::EntityType *m_entityType;
};


} // namespace MainWindowNS
#endif // MAINWINDOWNS_ATTRIBUTEEDITOR_H

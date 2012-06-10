#ifndef MAINWINDOWNS_RELATIONSEDITOR_H
#define MAINWINDOWNS_RELATIONSEDITOR_H

#include <QDialog>

namespace LBDatabase {
class Relation;
class EntityType;
}

namespace MainWindowNS {

namespace Ui {
class RelationsEditor;
}

class RelationEditor : public QDialog
{
    Q_OBJECT
    
public:
    explicit RelationEditor(LBDatabase::EntityType *entityType, QWidget *parent = 0);
    ~RelationEditor();

    void setRelation(LBDatabase::Relation *relation);

private slots:

    void checkCheckboxStates();

    void showTransposeRelation();

    void on_buttonBox_accepted();
    void checkLineEditContents();

private:
    Ui::RelationsEditor *ui;
    LBDatabase::Relation *m_relation;
    LBDatabase::EntityType *m_entityType;

    QPushButton *m_pushButtonShowTranspose;
};


} // namespace MainWindowNS
#endif // MAINWINDOWNS_RELATIONSEDITOR_H

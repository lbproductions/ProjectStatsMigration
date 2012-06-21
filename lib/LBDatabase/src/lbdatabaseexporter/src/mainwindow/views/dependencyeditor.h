#ifndef MAINWINDOWNS_DEPENDENCYEDITOR_H
#define MAINWINDOWNS_DEPENDENCYEDITOR_H

#include <QDialog>
#include <LBDatabase/property.h>

namespace LBDatabase {
class DependencyMetaData;
class EntityType;
}

namespace MainWindowNS {

namespace Ui {
class DependencyEditor;
}

class DependencyEditor : public QDialog
{
    Q_OBJECT
    
public:
    explicit DependencyEditor(LBDatabase::EntityType *entityType, QWidget *parent = 0);
    ~DependencyEditor();
    
    void setDependencyMetaData(const LBDatabase::DependencyMetaData &metaData);

private slots:
    void relationChanged(int);

    void save();


private:
    void addPossibleDependencies(LBDatabase::EntityType *dependencyType);
    void addParentDependencies(LBDatabase::EntityType *dependencyType);

    Ui::DependencyEditor *ui;

    LBDatabase::DependencyMetaData m_metaData;
    LBDatabase::EntityType *m_entityType;
};


} // namespace MainWindowNS
#endif // MAINWINDOWNS_DEPENDENCYEDITOR_H

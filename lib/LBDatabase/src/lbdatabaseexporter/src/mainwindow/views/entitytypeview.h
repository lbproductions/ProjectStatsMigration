#ifndef MAINWINDOWNS_ENTITYTYPEVIEW_H
#define MAINWINDOWNS_ENTITYTYPEVIEW_H

#include <LBGui/LBGui.h>

class QStandardItemModel;
class QModelIndex;

class MainWindow;

namespace LBDatabase {
class EntityType;
class Relation;
}

namespace MainWindowNS {

namespace Ui {
class EntityTypeView;
}

class EntityTypeView : public LBGui::View
{
    Q_OBJECT
    
public:
    explicit EntityTypeView(MainWindow *parent = 0);
    ~EntityTypeView();
    
    void setEntityType(LBDatabase::EntityType *entityType);

public slots:
    void activated();

    void addAttribute();
    void addFunction();
    void addRelation();

    void editAttribute();
    void editFunction();
    void editRelation();

private slots:
    void refreshContents();

    void on_pushButtonEditAttribute_clicked();
    void on_pushButtonAddAttribute_clicked();
    void on_pushButtonRemoveAttribute_clicked();

    void on_pushButtonEditFunction_clicked();
    void on_pushButtonAddFunction_clicked();

    void on_pushButtonEditRelation_clicked();
    void on_pushButtonAddRelation_clicked();

    void attributeSelectionChanged(const QModelIndex & current, const QModelIndex & previous);
    void functionSelectionChanged(const QModelIndex & current, const QModelIndex & previous);
    void relationSelectionChanged(const QModelIndex & current, const QModelIndex & previous);

    void on_treeViewAttributes_doubleClicked(const QModelIndex &index);
    void on_treeViewFunctions_doubleClicked(const QModelIndex &index);
    void on_treeViewRelations_doubleClicked(const QModelIndex &index);

    void addRelationToModel(int row, LBDatabase::Relation *relation);

private:
    Ui::EntityTypeView *ui;

    MainWindow *m_parent;

    LBDatabase::EntityType *m_entityType;

    QStandardItemModel *m_attributesModel;
    QStandardItemModel *m_relationsModel;
    QStandardItemModel *m_functionsModel;
};


} // namespace MainWindowNS
#endif // MAINWINDOWNS_ENTITYTYPEVIEW_H

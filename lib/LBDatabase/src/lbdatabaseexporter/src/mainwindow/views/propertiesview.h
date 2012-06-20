#ifndef MAINWINDOWNS_PROPERTIESVIEW_H
#define MAINWINDOWNS_PROPERTIESVIEW_H

#include <QWidget>

class QStandardItemModel;
class QModelIndex;

class MainWindow;

namespace LBDatabase {
class EntityType;
class Relation;
}

namespace MainWindowNS {

class Actions;

namespace Ui {
class PropertiesView;
}

class PropertiesView : public QWidget
{
    Q_OBJECT
    
public:
    explicit PropertiesView(QWidget *parent = 0);
    ~PropertiesView();
    
    void setEntityType(LBDatabase::EntityType *entityType);

public slots:
    void activateActions(Actions *actions);

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
    Ui::PropertiesView *ui;

    Actions *m_actions;
    LBDatabase::EntityType *m_entityType;

    QStandardItemModel *m_attributesModel;
    QStandardItemModel *m_relationsModel;
    QStandardItemModel *m_functionsModel;
};


} // namespace MainWindowNS
#endif // MAINWINDOWNS_PROPERTIESVIEW_H

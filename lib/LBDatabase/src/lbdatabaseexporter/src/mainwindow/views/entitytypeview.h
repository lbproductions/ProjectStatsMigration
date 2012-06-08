#ifndef MAINWINDOWNS_ENTITYTYPEVIEW_H
#define MAINWINDOWNS_ENTITYTYPEVIEW_H

#include <QWidget>

class QStandardItemModel;
class QModelIndex;

namespace LBDatabase {
class EntityType;
}

namespace MainWindowNS {

namespace Ui {
class EntityTypeView;
}

class EntityTypeView : public QWidget
{
    Q_OBJECT
    
public:
    explicit EntityTypeView(QWidget *parent = 0);
    ~EntityTypeView();
    
    void setEntityType(LBDatabase::EntityType *entityType);


private slots:
    void on_pushButtonEditAttribute_clicked();

    void on_pushButtonAddAttribute_clicked();

    void on_pushButtonRemoveAttribute_clicked();

    void refreshContents();

    void on_pushButtonEditFunction_clicked();

    void on_pushButtonAddFunction_clicked();


    void attributeSelectionChanged(const QModelIndex & current, const QModelIndex & previous);
    void functionSelectionChanged(const QModelIndex & current, const QModelIndex & previous);

    void on_treeViewAttributes_doubleClicked(const QModelIndex &index);
    void on_treeViewFunctions_doubleClicked(const QModelIndex &index);

private:
    Ui::EntityTypeView *ui;

    LBDatabase::EntityType *m_entityType;

    QStandardItemModel *m_attributesModel;
    QStandardItemModel *m_relationsModel;
    QStandardItemModel *m_functionsModel;
};


} // namespace MainWindowNS
#endif // MAINWINDOWNS_ENTITYTYPEVIEW_H

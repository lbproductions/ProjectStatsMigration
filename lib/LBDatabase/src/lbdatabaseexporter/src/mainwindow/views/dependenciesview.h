#ifndef MAINWINDOWNS_DEPENDENCIESVIEW_H
#define MAINWINDOWNS_DEPENDENCIESVIEW_H

#include <QWidget>

class QStandardItemModel;

namespace LBDatabase {
class EntityType;
class Property;
}

namespace MainWindowNS {

class Ui_DependenciesView;

class DependenciesView : public QWidget
{
    Q_OBJECT
public:
    explicit DependenciesView(QWidget *parent = 0);

    void setEntityType(LBDatabase::EntityType *entityType);

private slots:
    void addDependency();

private:
    QString makeRelationName(LBDatabase::Property *dependency, int relationId);
signals:
private:
    Ui_DependenciesView *ui;
    QStandardItemModel *m_dependenciesModel;

    LBDatabase::EntityType *m_entityType;
    
};

} // namespace MainWindowNS

#endif // MAINWINDOWNS_DEPENDENCIESVIEW_H

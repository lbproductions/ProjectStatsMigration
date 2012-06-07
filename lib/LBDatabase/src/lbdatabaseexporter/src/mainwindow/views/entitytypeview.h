#ifndef MAINWINDOWNS_ENTITYTYPEVIEW_H
#define MAINWINDOWNS_ENTITYTYPEVIEW_H

#include <QWidget>

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

private:
    Ui::EntityTypeView *ui;

    LBDatabase::EntityType *m_entityType;
};


} // namespace MainWindowNS
#endif // MAINWINDOWNS_ENTITYTYPEVIEW_H

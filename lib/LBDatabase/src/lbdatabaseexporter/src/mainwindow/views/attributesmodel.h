#ifndef MAINWINDOWNS_ATTRIBUTESMODEL_H
#define MAINWINDOWNS_ATTRIBUTESMODEL_H

#include <QStandardItemModel>

namespace LBDatabase {
class EntityType;
}

namespace MainWindowNS {

class AttributesModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit AttributesModel(QObject *parent = 0);
    
    void setEntityType(LBDatabase::EntityType *entityType);

private:
    LBDatabase::EntityType *m_entityType;
    
};

} // namespace MainWindowNS

#endif // MAINWINDOWNS_ATTRIBUTESMODEL_H

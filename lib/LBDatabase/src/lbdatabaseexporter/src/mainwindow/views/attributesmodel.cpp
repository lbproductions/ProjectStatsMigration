#include "attributesmodel.h"

#include <LBDatabase/LBDatabase.h>

namespace MainWindowNS {

AttributesModel::AttributesModel(QObject *parent) :
    QStandardItemModel(parent),
    m_entityType(0)
{
}

void AttributesModel::setEntityType(LBDatabase::EntityType *entityType)
{
    m_entityType = entityType;

    int row = 0;
    foreach(LBDatabase::Attribute *attribute, entityType->attributes()) {
        QStandardItem *itemName = new QStandardItem(attribute->identifier());
        setItem(row, 0, itemName);
        QStandardItem *itemType = new QStandardItem(attribute->qtType());
        setItem(row, 1, itemType);
        row++;
    }

    QStringList headerTitles;
    headerTitles << tr("Identifier") << tr("Qt-Type");
    setHorizontalHeaderLabels(headerTitles);
}

} // namespace MainWindowNS

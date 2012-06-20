#include "dependenciesview.h"
#include "ui_dependenciesview.h"

#include "dependencyeditor.h"

#include <LBGui/LBGui.h>
#include <LBDatabase/LBDatabase.h>

#include <QScrollArea>
#include <QVBoxLayout>

namespace MainWindowNS {

DependenciesView::DependenciesView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui_DependenciesView),
    m_entityType(0)
{
    ui->setupUi(this);

    setBackgroundRole(QPalette::Base);
    ui->scrollAreaWidgetContents->layout()->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    setContentsMargins(0,0,0,0);
    layout()->setSpacing(0);
    layout()->setContentsMargins(0,0,0,0);

    QFile stylesheet(QLatin1String(":/groupbox/itunes_white/stylesheet"));
    stylesheet.open(QFile::ReadOnly);
    ui->groupBoxDependencies->setStyleSheet(stylesheet.readAll());
    stylesheet.close();

    ui->treeViewDependencies->setAttribute(Qt::WA_MacShowFocusRect, false);

    QString style = "QTreeView {"
            "font-size: 13px;"
            "background-color: #f5f5f5;"
            "alternate-background-color: #ebebeb;"
            "selection-background-color: #Dbdbdb;"
            "selection-color: black;"
            "border: 1px solid #c5c5c5;"
            "}"

        "QTreeView::item {"
            "height: 22px;"
        "}";
    ui->treeViewDependencies->setStyleSheet(style);

    connect(ui->pushButtonAddDependency, SIGNAL(clicked()), this, SLOT(addDependency()));
}

void DependenciesView::setEntityType(LBDatabase::EntityType *entityType)
{
    m_entityType = entityType;
    m_dependenciesModel = new QStandardItemModel(this);
    int row = 0;
    foreach(LBDatabase::Property *p, entityType->properties()) {
        foreach(LBDatabase::DependencyMetaData metaData, p->dependencies()) {
            LBDatabase::Property *dependency = entityType->context()->storage()->property(metaData.dependencyPropertyType, metaData.dependencyPropertyId);
            QStandardItem *item = new QStandardItem(p->identifier());
            item->setEditable(false);
            m_dependenciesModel->setItem(row, 0, item);
            item = new QStandardItem(dependency->identifier());
            item->setEditable(false);
            m_dependenciesModel->setItem(row, 1, item);

            item = new QStandardItem(makeRelationName(dependency, metaData.entityRelation));
            item->setEditable(false);
            m_dependenciesModel->setItem(row, 2, item);
            ++row;
        }
    }

    QStringList dependenciesHeaderTitles;
    dependenciesHeaderTitles << tr("Property") << tr("Depends on") << tr("Of");
    m_dependenciesModel->setHorizontalHeaderLabels(dependenciesHeaderTitles);

    ui->treeViewDependencies->setModel(m_dependenciesModel);
}

void DependenciesView::addDependency()
{
    DependencyEditor editor(m_entityType, this);
    editor.setWindowModality(Qt::WindowModal);
    editor.exec();
}

QString DependenciesView::makeRelationName(LBDatabase::Property *dependency, int relationId)
{
    if(relationId == -1) {
        return tr("Self");
    }
    else if(relationId == 0) {
        return tr("All %1").arg(dependency->entityType()->displayNamePlural());
    }
    else {
        LBDatabase::Relation *relation = static_cast<LBDatabase::Relation *>(dependency->entityType()->context()->storage()->property(LBDatabase::Property::Relation,
                                                                                      relationId));
        return tr("All %1 in Self::%2").arg(relation->entityTypeOther()->displayNamePlural()).arg(relation->identifier());
    }
}

} // namespace MainWindowNS

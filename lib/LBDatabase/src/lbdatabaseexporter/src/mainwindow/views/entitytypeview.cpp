#include "entitytypeview.h"

#include "propertiesview.h"
#include "dependenciesview.h"
#include "../mainwindow.h"
#include "../controller.h"

#include <LBDatabase/LBDatabase.h>

#include <QLineEdit>
#include <QSettings>

namespace MainWindowNS {

EntityTypeView::EntityTypeView(MainWindow *parent) :
    LBGui::View(parent),
    m_mainWindow(parent)
{
    QVBoxLayout *l = new QVBoxLayout(this);
    l->setContentsMargins(0,0,0,0);
    l->setSpacing(0);
    setLayout(l);

    LBGui::TabWidget *tabWidget = new LBGui::TabWidget(this);
    tabWidget->setStyle(LBGui::TabWidget::ItunesWhite);
    l->addWidget(tabWidget);

    m_propertiesView = new PropertiesView(this);
    tabWidget->addTab(m_propertiesView, tr("Properties"));

    m_dependenciesView = new DependenciesView(this);
    tabWidget->addTab(m_dependenciesView, tr("Dependencies"));

    LBGui::ItunesApplyBar *applyBar = new LBGui::ItunesApplyBar(this);

    QWidget *sourceWidget = new QWidget(applyBar);
    QHBoxLayout *sourceLayout = new QHBoxLayout(sourceWidget);
    sourceWidget->setLayout(sourceLayout);
    LBGui::Label *label = new LBGui::Label(tr("Export C++ Source to:"));
    label->setForegroundColor(QColor(251,251,251));
    label->setDropshadowColor(QColor(67,67,67));
    label->setFont(QFont("Lucida Grande", 12, QFont::Bold));
    sourceLayout->addWidget(label);
    m_lineEditSource = new QLineEdit(sourceWidget);
    QSettings settings;
    m_lineEditSource->setText(settings.value("storagecppsource").toString());
    connect(m_lineEditSource, SIGNAL(textChanged(QString)), this, SLOT(sourceLocationChanged(QString)));
    sourceLayout->addWidget(m_lineEditSource);
    applyBar->setWidget(sourceWidget);

    layout()->addWidget(applyBar);

    connect(applyBar, SIGNAL(applyClicked()), this, SLOT(exportSource()));
}

void EntityTypeView::setEntityType(LBDatabase::EntityType *entityType)
{
    if(m_entityType == entityType)
        return;

    m_entityType = entityType;

    m_propertiesView->setEntityType(entityType);
    m_dependenciesView->setEntityType(entityType);
}

QString EntityTypeView::sourceLocation() const
{
    return m_lineEditSource->text();
}

PropertiesView *EntityTypeView::propertiesView() const
{
    return m_propertiesView;
}

void EntityTypeView::activated()
{
    m_propertiesView->activateActions(m_mainWindow->controller()->actions());

    QSettings settings;
    m_lineEditSource->setText(settings.value("storagecppsource").toString());
}

void EntityTypeView::sourceLocationChanged(QString location)
{
    QSettings settings;
    settings.setValue("storagecppsource", location);
}

void EntityTypeView::exportSource()
{
    m_mainWindow->controller()->exportSource(m_lineEditSource->text());
}

} // namespace MainWindowNS

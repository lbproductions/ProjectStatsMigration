#include "listview.h"

#include "contexttreeview.h"

#include "../controller.h"
#include "../mainwindow.h"

#include <LBDatabase/LBDatabase.h>
#include <LBGui/LBGui.h>

#include <QHBoxLayout>
#include <QScrollArea>

namespace MainWindowNS {

ListView::ListView(Controller *controller, MainWindow *parent) :
    QWidget(parent),
    m_context(0),
    m_controller(controller)
{
    setLayout(new QHBoxLayout(this));
    layout()->setContentsMargins(0,0,0,0);

    m_horizontalSplitter = new LBGui::Splitter(Qt::Vertical,this);
    m_horizontalSplitter->setStretchFactor(0, 0);
    m_horizontalSplitter->setStretchFactor(1, 1);
    layout()->addWidget(m_horizontalSplitter);

    m_contextTreeView = new ContextTreeView(this);
    connect(m_contextTreeView, SIGNAL(selectionChanged()), this, SLOT(onSelectionChanged()));
    connect(m_contextTreeView, SIGNAL(doubleClicked()), this, SLOT(onDoubleClick()));
    m_horizontalSplitter->addWidget(m_contextTreeView);
    m_horizontalSplitter->setStyle(LBGui::Splitter::MacOSStyle);

    LBGui::BackgroundWidget *scrollArea = new LBGui::BackgroundWidget(m_horizontalSplitter);
    scrollArea->setStyle(LBGui::BackgroundWidget::Gray);

    m_sheet = new LBGui::Sheet(scrollArea);
    m_sheet->setVisible(false);
    scrollArea->setWidget(m_sheet);

    m_horizontalSplitter->addWidget(scrollArea);
}

ListView::~ListView()
{
}

void ListView::setContext(LBDatabase::Context *context)
{
    m_contextTreeView->setContext(context);
}

void ListView::onSelectionChanged()
{
    LBDatabase::Entity *entity = m_contextTreeView->firstSelectedEntity();
    m_sheet->setHeaderTitle(entity->displayName());
    m_sheet->setVisible(true);
}

void ListView::onDoubleClick()
{
    LBDatabase::Entity *entity = m_contextTreeView->firstSelectedEntity();
    m_controller->openEntityWindow(entity);
}

//void ListView::saveSettings()
//{
//    QSettings settings;
//    QString path = QString(m_categorie->metaObject()->className()) + "/ListView/";

//    settings.setValue(path+"horizontalSplitter/Geometry",m_horizontalSplitter->saveGeometry());
//    settings.setValue(path+"horizontalSplitter/WindowState",m_horizontalSplitter->saveState());
//    settings.setValue(path+"rowList/header/sortIndicatorSection",m_rowList->header()->sortIndicatorSection());
//    settings.setValue(path+"rowList/header/sortIndicatorOrder",m_rowList->header()->sortIndicatorOrder());
//    settings.setValue(path+"rowList/header/geometry",m_rowList->header()->saveGeometry());
//    settings.setValue(path+"rowList/header/state",m_rowList->header()->saveState());
//}

//void ListView::restoreSettings()
//{
//    QSettings settings;
//    QString path = QString(m_categorie->metaObject()->className()) + "/ListView/";

//    m_horizontalSplitter->restoreGeometry(settings.value(path+"horizontalSplitter/Geometry").toByteArray());
//    m_horizontalSplitter->restoreState(settings.value(path+"horizontalSplitter/WindowState").toByteArray());
//    m_rowList->header()->setSortIndicator(settings.value(path+"rowList/sortIndicatorSection").toInt(),
//					    (Qt::SortOrder)settings.value(path+"rowList/sortIndicatorOrder").toInt());
//    m_rowList->header()->restoreGeometry(settings.value(path+"rowList/header/geometry").toByteArray());
//    m_rowList->header()->restoreState(settings.value(path+"rowList/header/state").toByteArray());
//}

}

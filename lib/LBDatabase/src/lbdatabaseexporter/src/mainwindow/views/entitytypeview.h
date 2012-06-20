#ifndef MAINWINDOWNS_ENTITYTYPEVIEW_H
#define MAINWINDOWNS_ENTITYTYPEVIEW_H

#include <LBGui/LBGui.h>

class QLineEdit;

class MainWindow;

namespace LBDatabase {
class EntityType;
}

namespace MainWindowNS {

class PropertiesView;
class DependenciesView;

class EntityTypeView : public LBGui::View
{
    Q_OBJECT
public:
    EntityTypeView(MainWindow *parent = 0);

    void setEntityType(LBDatabase::EntityType *entityType);

    QString sourceLocation() const;
    PropertiesView *propertiesView() const;

public slots:
    void activated();

private slots:
    void sourceLocationChanged(QString location);
    void exportSource();

private:
    LBDatabase::EntityType *m_entityType;

    MainWindow *m_mainWindow;

    PropertiesView *m_propertiesView;
    DependenciesView *m_dependenciesView;

    QLineEdit *m_lineEditSource;
};

} // namespace MainWindowNS

#endif // MAINWINDOWNS_ENTITYTYPEVIEW_H

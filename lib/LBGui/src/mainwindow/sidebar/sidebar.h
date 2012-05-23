#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>

class QStandardItemModel;

namespace LBGui {

class MainWindow;

class SidebarTreeView;
class SidebarStatusBar;
class SidebarParentCategorie;
class SidebarChildCategorie;

class Sidebar : public QWidget
{
    Q_OBJECT
    Q_ENUMS(Style)

public:
    enum Style {
        MacOSLionMailStyle
    };

    explicit Sidebar(MainWindow *parent);

    Style style() const;
    void setStyle(Style style);

    SidebarParentCategorie *addParentCategorie(const QString& title);
    SidebarChildCategorie* addChildCategorie(int parentIndex, const QString& title);
    SidebarChildCategorie* addChildCategorie(int parentIndex, int childIndex, const QString &title);

    void removeCategorie(SidebarChildCategorie *categorie);

    void clearCategorie(int parentIndex);

    void setSelectedCategorie(int parent, int child);

public slots:
    void expandAll();

signals:
    void categorieChanged(::LBGui::SidebarChildCategorie*);

protected:
    Style m_style;

    MainWindow *m_mainWindow;

    SidebarStatusBar* m_statusBar;
    SidebarTreeView* m_treeView;
    QStandardItemModel* m_categoriesModel;
};

} // namespace LBGui

#endif // SIDEBAR_H

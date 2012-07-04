#ifndef LBGUI_SIDEBARPARENTCATEGORIE_H
#define LBGUI_SIDEBARPARENTCATEGORIE_H

#include <QStandardItem>

namespace LBGui {

class SidebarParentCategorie : public QStandardItem
{
public:
    enum Role {
        TitleRole = Qt::DisplayRole,
        SelfRole = Qt::UserRole + 1
    };

    explicit SidebarParentCategorie();
    explicit SidebarParentCategorie(const QString &title);

    void setTitle(const QString &title);
    QString title() const;

protected:
    QString m_title;
};

} // namespace LBGui

Q_DECLARE_METATYPE(LBGui::SidebarParentCategorie*)

#endif // LBGUI_SIDEBARPARENTCATEGORIE_H

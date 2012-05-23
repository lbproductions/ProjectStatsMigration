#ifndef LBGUI_SIDEBARCHILDCATEGORIE_H
#define LBGUI_SIDEBARCHILDCATEGORIE_H

#include <QStandardItem>

namespace LBGui {

class SidebarChildCategorie : public QObject, public QStandardItem
{
    Q_OBJECT
public:
    enum Role {
        SelfRole = Qt::UserRole + 1,
        TitleRole,
        WidgetRole,
        CustomDataRole,
        ModelIndexRole
    };

    explicit SidebarChildCategorie();
    explicit SidebarChildCategorie(const QString &title);

    void setTitle(const QString &title);
    QString title() const;

    void setWidget(QWidget *w);
    virtual QWidget *widget() const;

    int level() const;

signals:
    void categorieActivated();

protected:
    friend class SidebarTreeView;
    friend class Sidebar;

    void emitActivated();

    void setLevel(int level);

    QString m_title;
    QWidget *m_widget;
    int m_level;
};

} // namespace LBGui

Q_DECLARE_METATYPE(LBGui::SidebarChildCategorie*)

#endif // LBGUI_SIDEBARCHILDCATEGORIE_H

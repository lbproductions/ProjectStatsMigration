#include "sidebarparentcategorie.h"

namespace LBGui {

SidebarParentCategorie::SidebarParentCategorie() :
    QStandardItem()
{
}

SidebarParentCategorie::SidebarParentCategorie(const QString &title) :
    QStandardItem(title)
{
#ifdef Q_WS_MAC
    static QFont f;
    f.setFamily("Lucida Grande");
    f.setPixelSize(11);
    f.setBold(true);
    f.setCapitalization(QFont::AllUppercase);
    setFont(f);

    setFlags(Qt::ItemIsEnabled);
    setSizeHint(QSize(0,18));
#endif

    setData(QVariant::fromValue<SidebarParentCategorie*>(this),SelfRole);
    setTitle(title);
}

void SidebarParentCategorie::setTitle(const QString &title)
{
    m_title = title;
    setData(title, TitleRole);
}

QString SidebarParentCategorie::title() const
{
    return m_title;
}

} // namespace LBGui

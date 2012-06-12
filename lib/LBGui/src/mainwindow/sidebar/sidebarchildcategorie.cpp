#include "sidebarchildcategorie.h"

#include "../view.h"

namespace LBGui {

SidebarChildCategorie::SidebarChildCategorie() :
    QStandardItem(),
    m_title(QString()),
    m_view(0)
{
}

SidebarChildCategorie::SidebarChildCategorie(const QString &title) :
    QStandardItem(),
    m_title(title),
    m_view(0)
{
#ifdef Q_OS_MAC
    QFont f;
    f.setFamily("Lucida Grande");
    f.setPixelSize(13);
    setFont(f);

    setSizeHint(QSize(0,24));
    setFlags((flags() | Qt::ItemIsSelectable) & ~ Qt::ItemIsEditable);
#endif

    setData(QVariant::fromValue<SidebarChildCategorie*>(this),SelfRole);
    setTitle(title);
}

void SidebarChildCategorie::setTitle(const QString &title)
{
    m_title = title;
    setData(title, TitleRole);
}

QString SidebarChildCategorie::title() const
{
    return m_title;
}

void SidebarChildCategorie::setView(View *v)
{
    m_view = v;
    setData(QVariant::fromValue<QWidget*>(v), WidgetRole);
}

View *SidebarChildCategorie::view() const
{
    return m_view;
}

int SidebarChildCategorie::level() const
{
    return m_level;
}

void SidebarChildCategorie::setLevel(int level)
{
    m_level = level;
}

void SidebarChildCategorie::emitActivated()
{
    emit categorieActivated();
}



} // namespace LBGui

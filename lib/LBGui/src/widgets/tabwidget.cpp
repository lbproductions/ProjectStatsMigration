#include "tabwidget.h"

#include <QTabBar>
#include <QFile>
#include <QDebug>

namespace LBGui {

class TabBar : public QTabBar
{
public:
    TabBar(QWidget *parent = 0);
};

TabWidget::TabWidget(QWidget *parent) :
    QTabWidget(parent)
{
    setTabBar(new TabBar(this));
}

TabWidget::Style TabWidget::style() const
{
    return m_style;
}

void TabWidget::setStyle(Style style)
{
    QFile stylesheet;
    m_style = style;

    switch(m_style) {
    case ItunesWhite:
        stylesheet.setFileName(QLatin1String(":/tabwidget/itunes_white/stylesheet"));
        break;
    }

    if(!stylesheet.exists()) {
        qWarning() << "TabWidget::setStyle: The stylesheet file for the style does not exist.";
    }

    stylesheet.open(QFile::ReadOnly);
    setStyleSheet(stylesheet.readAll());
    stylesheet.close();
}

TabBar::TabBar(QWidget *parent) :
    QTabBar(parent)
{
}

} // namespace LBGui

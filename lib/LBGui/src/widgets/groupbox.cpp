#include "groupbox.h"

#include <QFile>
#include <QHBoxLayout>
#include <QDebug>

namespace LBGui {

GroupBox::GroupBox(QWidget *parent) :
    QGroupBox(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(5,5,5,5);
    layout->setSpacing(0);
    setLayout(layout);
}

GroupBox::Style GroupBox::style() const
{
    return m_style;
}

void GroupBox::setStyle(Style style)
{
    QFile stylesheet;
    m_style = style;

    switch(m_style) {
    case ItunesWhite:
        stylesheet.setFileName(QLatin1String(":/groupbox/itunes_white/stylesheet"));
        break;
    case IphotoDark:
        stylesheet.setFileName(QLatin1String(":/groupbox/iphoto_dark/stylesheet"));
        break;
    }

    if(!stylesheet.exists()) {
        qWarning() << "TabWidget::setStyle: The stylesheet file for the style does not exist.";
    }

    stylesheet.open(QFile::ReadOnly);
    setStyleSheet(stylesheet.readAll());
    stylesheet.close();
}

} // namespace LBGui

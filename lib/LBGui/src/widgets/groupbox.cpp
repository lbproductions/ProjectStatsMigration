#include "groupbox.h"

#include <QFile>

#include <QDebug>

GroupBox::GroupBox(QWidget *parent) :
    QGroupBox(parent)
{
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
    }

    if(!stylesheet.exists()) {
        qWarning() << "TabWidget::setStyle: The stylesheet file for the style does not exist.";
    }

    stylesheet.open(QFile::ReadOnly);
    setStyleSheet(stylesheet.readAll());
    stylesheet.close();
}

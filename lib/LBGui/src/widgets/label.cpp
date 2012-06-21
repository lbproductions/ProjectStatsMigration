#include "label.h"

#include <QPainter>
#include <QPaintEvent>

namespace LBGui {

Label::Label(const QString &text, QWidget *parent) :
    QLabel(text, parent)
{
}

void Label::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    if(m_dropshadowColor.isValid() && m_foregroundColor.isValid()) {
        p.setPen(m_dropshadowColor);
        QRect rect = contentsRect();
        p.setFont(font());
        p.drawText(rect,text());
        p.setPen(m_foregroundColor);
        rect.adjust(0,-1,0,-1);
        p.drawText(rect,text());
    }
    else {
        QLabel::paintEvent(e);
    }

}

void Label::setDropshadowColor(const QColor &color)
{
    m_dropshadowColor = color;
}

void Label::setForegroundColor(const QColor &color)
{
    m_foregroundColor = color;
}

} // namespace LBGui

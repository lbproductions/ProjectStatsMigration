#include "splitter.h"

#include <QPainter>

#include <QDebug>

namespace LBGui {

Splitter::Splitter(Qt::Orientation orientation, QWidget *parent) :
    QSplitter(orientation,parent),
    m_style(NoStyle)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

Splitter::Style Splitter::style() const
{
    return m_style;
}

void Splitter::setStyle(Style style)
{
    m_style = style;
}

Splitter::Direction Splitter::direction() const
{
    return m_direction;
}

void Splitter::setDirection(Direction direction)
{
    m_direction = direction;
}

SplitterHandle::SplitterHandle(Qt::Orientation orientation, Splitter *parent) :
    QSplitterHandle(orientation, parent),
    m_splitter(parent)
{
}

void SplitterHandle::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if(m_splitter->style() == Splitter::MacOSStyle) {
        if (orientation() == Qt::Vertical) {
            static QColor topColor(181, 181, 181);
            static QColor bottomColor(158, 158, 158);
            static QColor gradientStart(248, 248, 248);
            static QColor gradientStop(225, 225, 225);

            painter.setPen(topColor);
            painter.drawLine(0, 0, width(), 0);
            painter.setPen(bottomColor);
            painter.drawLine(0, height() - 1, width(), height() - 1);

            QLinearGradient linearGrad(QPointF(0, 0), QPointF(0, height() - 2));
            linearGrad.setColorAt(0, gradientStart);
            linearGrad.setColorAt(1, gradientStop);
            painter.fillRect(QRect(QPoint(0,1), size() - QSize(0, 2)), QBrush(linearGrad));

            painter.drawPixmap(width() / 2 - 2, 3, 4,4 , QPixmap(":/graphics/styles/mac/splitter/handle"));
            return;
        }
        else {
            static QColor color(181, 181, 181);
            painter.setPen(color);
            painter.drawLine(0, 0, 0, height());
            return;
        }
    }
    else if(m_splitter->style() == Splitter::MacOSFullscreenStyle) {
        if(m_splitter->direction() == Splitter::LeftToRight) {
            static QColor leftColor(78,77,79);
            static QColor rightColor(26,25,26);

            painter.setPen(leftColor);
            painter.drawLine(0, 0, 0, height());
            painter.setPen(rightColor);
            painter.drawLine(1, 0, 1, height());
            return;
        }
        else {
            static QColor leftColor(26,25,26);
            static QColor rightColor(78,77,79);

            painter.setPen(leftColor);
            painter.drawLine(2, 0, 2, height());
            painter.setPen(rightColor);
            painter.drawLine(3, 0, 3, height());
            return;
        }
    }
    QSplitterHandle::paintEvent(event);
}

QSize SplitterHandle::sizeHint() const
{
    QSize parentSize = QSplitterHandle::sizeHint();

    if(m_splitter->style() == Splitter::MacOSStyle) {
        if (orientation() == Qt::Vertical) {
            return parentSize + QSize(0, 2);
        }
        else {
            return QSize(1, height());
        }
    }
    else if(m_splitter->style() == Splitter::MacOSFullscreenStyle) {
        if (orientation() == Qt::Vertical) {
            return parentSize + QSize(0, 2);
        }
        else {
            return QSize(4, height());
        }
    }
    return parentSize;
}

QSplitterHandle *Splitter::createHandle()
{
    return new SplitterHandle(orientation(), this);
}

} // namespace LBGui

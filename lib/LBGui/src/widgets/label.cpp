#include "label.h"

#include <QPainter>
#include <QPaintEvent>

namespace LBGui {

Label::Label(const QString &text, QWidget *parent) :
    QLabel(text, parent),
    m_dragEnabled(false)
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

void Label::mouseReleaseEvent(QMouseEvent *event)
{
    QLabel::mouseReleaseEvent(event);

    if(event->button() == Qt::LeftButton)
        emit clicked();
}

void Label::mouseDoubleClickEvent(QMouseEvent *event)
{
    QLabel::mouseDoubleClickEvent(event);

    if(event->button() == Qt::LeftButton)
        emit doubleClicked();
}

void Label::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    if(m_dragEnabled) {
        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData;

        QByteArray encodedData;
        QDataStream stream(&encodedData, QIODevice::WriteOnly);
        stream << m_mimeData;

        mimeData->setData(m_mimeType, encodedData);
        drag->setMimeData(mimeData);
        if(pixmap())
            drag->setPixmap(pixmap()->scaled(20,45,Qt::KeepAspectRatio,Qt::SmoothTransformation));
        drag->exec();
    }
}

void Label::setDragEnabled(bool enabled)
{
    m_dragEnabled = enabled;
}

void Label::setMimeType(const QString &mimeType)
{
    m_mimeType = mimeType;
}

void Label::setMimeData(const QVariant &mimeData)
{
    m_mimeData = mimeData;
}

} // namespace LBGui

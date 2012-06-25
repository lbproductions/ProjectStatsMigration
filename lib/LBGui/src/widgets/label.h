#ifndef LBGUI_LABEL_H
#define LBGUI_LABEL_H

#include <QLabel>

#include <QVariant>

namespace LBGui {

class Label : public QLabel
{
    Q_OBJECT
public:
    explicit Label(const QString &text, QWidget *parent = 0);
    
    void paintEvent(QPaintEvent *);

    void setForegroundColor(const QColor &color);
    void setDropshadowColor(const QColor &color);

    void mousePressEvent(QMouseEvent *);

    void setDragEnabled(bool enabled);
    void setMimeType(const QString &mimeType);
    void setMimeData(const QVariant &mimeData);

signals:
    void clicked();
    void doubleClicked();

protected:
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);

private:
    QColor m_foregroundColor;
    QColor m_dropshadowColor;

    QString m_mimeType;
    QVariant m_mimeData;

    bool m_dragEnabled;
};

} // namespace LBGui

#endif // LBGUI_LABEL_H

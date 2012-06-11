#ifndef LBGUI_LABEL_H
#define LBGUI_LABEL_H

#include <QLabel>

namespace LBGui {

class Label : public QLabel
{
    Q_OBJECT
public:
    explicit Label(const QString &text, QWidget *parent = 0);
    
    void paintEvent(QPaintEvent *);

    void setForegroundColor(const QColor &color);
    void setDropshadowColor(const QColor &color);

private:
    QColor m_foregroundColor;
    QColor m_dropshadowColor;
};

} // namespace LBGui

#endif // LBGUI_LABEL_H

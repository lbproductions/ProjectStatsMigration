#ifndef SPLITTER_H
#define SPLITTER_H

#include <QSplitter>

namespace LBGui
{

class Splitter;

class SplitterHandle : public QSplitterHandle
{
Q_OBJECT
public:
    SplitterHandle(Qt::Orientation orientation, Splitter *parent);
    void paintEvent(QPaintEvent * event);
    QSize sizeHint() const;

private:
    Splitter* m_splitter;
};

class Splitter : public QSplitter
{
    Q_OBJECT
    Q_ENUMS(Style)
    Q_ENUMS(Direction)

public:
    enum Style {
        NoStyle,
        MacOSStyle,
        MacOSFullscreenStyle
    };
    enum Direction {
        NoDirection,
        LeftToRight,
        RightToLeft,
        TopToBottom,
        BottomToTop
    };

    Splitter(Qt::Orientation orientation, QWidget *parent = 0);

    Style style() const;

    void setStyle(Style style);

    Direction direction() const;

    void setDirection(Direction direction);

    QSplitterHandle *createHandle();

private:
    Style m_style;
    Direction m_direction;
};

} // namespace LBGui

#endif // SPLITTER_H

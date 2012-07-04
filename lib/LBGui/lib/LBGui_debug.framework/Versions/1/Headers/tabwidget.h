#ifndef LEAGUEVIEW_H
#define LEAGUEVIEW_H

#include <QTabWidget>

namespace LBGui {

class TabWidget : public QTabWidget
{
    Q_ENUMS(Style)

public:
    enum Style {
        ItunesWhite
    };

    TabWidget(QWidget* parent = 0);

    Style style() const;

    void setStyle(Style style);

private:
    Style m_style;
};

} // namespace LBGui

#endif // LEAGUEVIEW_H

#ifndef GROUPBOX_H
#define GROUPBOX_H

#include <QGroupBox>

namespace LBGui {

class GroupBox : public QGroupBox
{
    Q_OBJECT

public:
    enum Style {
        ItunesWhite,
        IphotoDark
    };

    explicit GroupBox(QWidget *parent = 0);

    Style style() const;
    void setStyle(Style style);

private:
    Style m_style;
    
};

} // namespace LBGui

#endif // GROUPBOX_H

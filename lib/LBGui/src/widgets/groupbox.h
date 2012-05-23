#ifndef GROUPBOX_H
#define GROUPBOX_H

#include <QGroupBox>

class GroupBox : public QGroupBox
{
    Q_OBJECT

public:
    enum Style {
        ItunesWhite
    };

    explicit GroupBox(QWidget *parent = 0);

    Style style() const;

    void setStyle(Style style);

private:
    Style m_style;
    
};

#endif // GROUPBOX_H

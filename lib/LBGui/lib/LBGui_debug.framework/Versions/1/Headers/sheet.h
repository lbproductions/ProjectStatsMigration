#ifndef LBGUI_SHEET_H
#define LBGUI_SHEET_H

#include <QFrame>

class QLabel;

namespace LBGui {

class Sheet : public QFrame
{
    Q_OBJECT
public:
    explicit Sheet(QWidget *parent = 0);

    void setHeaderIcon(const QIcon &icon);
    void setHeaderTitle(const QString &title);

    void setWidget(QWidget* widget);

private:
    QWidget *m_header;
    QLabel *m_iconLabel;
    QLabel *m_titleLabel;
    QWidget *m_widget;
};

}

#endif // LBGUI_SHEET_H

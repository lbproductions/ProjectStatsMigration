#ifndef LBGUI_LISTEDITBUTTONSWIDGET_H
#define LBGUI_LISTEDITBUTTONSWIDGET_H

#include <QWidget>

class QPushButton;

namespace LBGui {

class ListEditButtonsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ListEditButtonsWidget(QWidget *parent = 0);

signals:
    void addClicked();
    void removeClicked();
    void editClicked();

private:
    QPushButton *m_addButton;
    QPushButton *m_removeButton;
    QPushButton *m_editButton;
};

} // namespace LBGui

#endif // LBGUI_LISTEDITBUTTONSWIDGET_H

#ifndef ROWLISTHEADER_H
#define ROWLISTHEADER_H

#include <QHeaderView>

namespace LBGui {

class TreeViewHeader : public QHeaderView
{
    Q_OBJECT
public:
    TreeViewHeader(Qt::Orientation orientation, QWidget * parent = 0 );

private slots:
    void hideHeader(bool hide);

protected:
    virtual void mousePressEvent(QMouseEvent* e);

private:
    QMenu *m_menu;
};

} //namespace LBGui

#endif // ROWLISTHEADER_H

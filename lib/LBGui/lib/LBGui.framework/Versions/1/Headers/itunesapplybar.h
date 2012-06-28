#ifndef LBGUI_ITUNESAPPLYBAR_H
#define LBGUI_ITUNESAPPLYBAR_H

#include <QWidget>

#include <QHBoxLayout>

namespace LBGui {

class ItunesApplyBar : public QWidget
{
    Q_OBJECT
public:
    explicit ItunesApplyBar(QWidget *parent = 0);
    
    void setWidget(QWidget *widget);

signals:
    void applyClicked();
private:
    QHBoxLayout *m_contentLayout;
};

} // namespace LBGui

#endif // LBGUI_ITUNESAPPLYBAR_H

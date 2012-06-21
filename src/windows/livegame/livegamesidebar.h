#ifndef LIVEGAMEWINDOWNS_SIDEBAR_H
#define LIVEGAMEWINDOWNS_SIDEBAR_H

#include <QWidget>

class QStackedLayout;
class QHBoxLayout;
class QButtonGroup;

namespace LiveGameWindowNS {

class SidebarPage;

class LiveGameSidebar : public QWidget
{
    Q_OBJECT
public:
    explicit LiveGameSidebar(QWidget *parent = 0);
    
    void addPage(const QString &title, SidebarPage *sidebarPage);
    void insertPage(int index, const QString &title, SidebarPage *sidebarPage);
    
private slots:
    void setCurrentPage(int id);

private:
    QStackedLayout *m_stackedLayout;
    QHBoxLayout *m_layoutPageButtons;
    QButtonGroup *m_buttonGroup;
    QList<SidebarPage *> m_sidebarPages;
};

} // namespace LiveGameWindowNS

#endif // LIVEGAMEWINDOWNS_SIDEBAR_H

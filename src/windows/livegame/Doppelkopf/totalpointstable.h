#ifndef DOKOLIVEGAMEWINDOWNS_TOTALPOINTSTABLE_H
#define DOKOLIVEGAMEWINDOWNS_TOTALPOINTSTABLE_H

#include <QTableWidget>

class DoppelkopfLiveGame;

namespace DokoLiveGameWindowNS {

class TotalPointsTable : public QTableWidget
{
    Q_OBJECT
public:
    explicit TotalPointsTable(QWidget *parent = 0);

    void setDoppelkopfLiveGame(DoppelkopfLiveGame *doppelkopfLiveGame);
    
    void resizeEvent(QResizeEvent *event);

private slots:
    void updateContents();

private:
    DoppelkopfLiveGame *m_doppelkopfLiveGame;
};

} // namespace DokoLiveGameWindowNS

#endif // DOKOLIVEGAMEWINDOWNS_TOTALPOINTSTABLE_H

#ifndef DOKOLIVEGAMEWINDOWNS_CENTRALWIDGET_H
#define DOKOLIVEGAMEWINDOWNS_CENTRALWIDGET_H

#include <QWidget>

class DoppelkopfLiveGame;
class DokoLiveGameWindow;
class DokoLiveGameGraphView;

namespace DokoLiveGameWindowNS {

class CentralWidget : public QWidget
{

public:
    explicit CentralWidget(DokoLiveGameWindow *parent = 0);
    ~CentralWidget();

    void setDoppelkopfLiveGame(DoppelkopfLiveGame *doppelkopfLiveGame);

private:
    DoppelkopfLiveGame *m_doppelkopfLiveGame;

    DokoLiveGameGraphView *m_graphView;
};

}

#endif // DOKOLIVEGAMEWINDOWNS_CENTRALWIDGET_H

#ifndef LISTVIEW_H
#define LISTVIEW_H

#include <LBGui/LBGui.h>

class MainWindow;
class ContextTreeView;

namespace LBDatabase {
class Context;
}

namespace LBGui {
class Sheet;
class Splitter;
}

namespace MainWindowNS {

class Controller;

class ListView : public LBGui::View
{
    Q_OBJECT
public:
    explicit ListView(MainWindowNS::Controller *controller, MainWindow *parent = 0);
    ~ListView();

    void setContext(LBDatabase::Context *context);

private slots:
    void onSelectionChanged();
    void onDoubleClick();

private:
    Controller *m_controller;
    LBGui::Sheet *m_sheet;
    LBGui::Splitter *m_horizontalSplitter;
    ContextTreeView *m_contextTreeView;

    LBDatabase::Context *m_context;
};

}

#endif // LISTVIEW_H

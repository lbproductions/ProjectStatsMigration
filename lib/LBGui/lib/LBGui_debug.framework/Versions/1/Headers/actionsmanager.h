#ifndef ACTIONSMANAGER_H
#define ACTIONSMANAGER_H

#include <QObject>
#include <QMultiHash>

class QAction;

namespace LBGui {

class MainWindow;
class Action;

class ActionsManager : public QObject
{
    Q_OBJECT
    Q_ENUMS(Context)
public:
    enum Context {
        AnyContext = 0
    };

    static ActionsManager *globalInstance();

    void addAction(Action *action, Context context = AnyContext);

    Action *minimizeAction();

    Action *zoomAction();

    Action *bringAllToFrontAction();

    Action *addWindowAction(QWidget *w);

protected slots:
    void on_minimize();
    void on_zoom();
    void bringAllToFront();
    void on_windowAction();
    void on_windowTitleChanged();

protected:
    ActionsManager(QObject *parent = 0);

    Action *windowAction(QWidget *w);

    bool eventFilter(QObject *, QEvent *);

    QList<Action*> m_actions;
    QHash<QWidget*, Action*> m_windowActions;

private:
    static ActionsManager *s_instance;


};

} // namespace LBGui

#endif // ACTIONSMANAGER_H

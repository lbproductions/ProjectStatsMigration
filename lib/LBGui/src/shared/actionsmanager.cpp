#include "actionsmanager.h"

#include "action.h"

#include <mainwindow/mainwindow.h>

#include <QMutex>
#include <QEvent>
#include <QApplication>
#include <QVariant>
#include <QPointer>

#include <QDebug>

Q_DECLARE_METATYPE(QPointer<QWidget>)

namespace LBGui {

ActionsManager *ActionsManager::s_instance(0);

ActionsManager *ActionsManager::globalInstance()
{
    static QMutex mutex;
    static QObject guard;
    QMutexLocker locker(&mutex); (void) locker;

    if(s_instance) {
        return s_instance;
    }

    s_instance = new ActionsManager(&guard);
    QApplication::instance()->installEventFilter(s_instance);
    return s_instance;
}

void ActionsManager::addAction(Action *action, ActionsManager::Context context)
{
    if(!m_actions.contains(action)) {
        m_actions.append(action);
    }
}

Action *ActionsManager::zoomAction()
{
    static Action *action = new Action(this);
    action->setText(tr("Zoom"));
    connect(action, SIGNAL(triggered()), this, SLOT(on_zoom()));
    return action;
}

Action *ActionsManager::minimizeAction()
{
    static Action *action = new Action(this);
    action->setText(tr("Minimize"));
    action->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_M));
    connect(action, SIGNAL(triggered()), this, SLOT(on_minimize()));
    return action;
}

Action *ActionsManager::bringAllToFrontAction()
{
    static Action *action = new Action(this);
    action->setText(tr("Bring all to front"));
    connect(action, SIGNAL(triggered()), this, SLOT(bringAllToFront()));
    return action;
}

Action *ActionsManager::windowAction(QWidget *w)
{
    Action *action = new Action(this);
    action->setText(w->windowTitle());
    action->setData(QVariant::fromValue<QPointer<QWidget> >(w));
    action->setCheckable(true);
    action->setChecked(true);
    connect(action, SIGNAL(triggered()), this, SLOT(on_windowAction()));
    MainWindow* mw = qobject_cast<MainWindow*>(w);
    if(mw) {
        connect(mw,SIGNAL(windowTitleChanged()),this, SLOT(on_windowTitleChanged()));
    }
    return action;
}

Action *ActionsManager::addWindowAction(QWidget *w)
{
    if(m_windowActions.contains(w)) {
        return 0;
    }

    Action *action = windowAction(w);
    m_windowActions.insert(w, action);
    return action;
}

void ActionsManager::on_minimize()
{
    QWidget *w = QApplication::activeWindow();
    if(w) {
        w->setWindowState(w->windowState() | Qt::WindowMinimized);
    }
}

void ActionsManager::on_zoom()
{
    QWidget *w = QApplication::activeWindow();
    if(w) {
        w->setWindowState(w->windowState() & Qt::WindowMaximized);
    }
}

void ActionsManager::bringAllToFront()
{
    QWidget *activeWindow = QApplication::activeWindow();
    foreach(QWidget *w, QApplication::topLevelWidgets()) {
        if(w->windowType() == Qt::Window && w->isHidden()) {
            w->show();
        }
    }
    if(activeWindow) {
        activeWindow->show();
    }
}

void ActionsManager::on_windowAction()
{
    Action *a = static_cast<Action*>(sender());
    QPointer<QWidget> w = a->data().value<QPointer<QWidget> >();
    if(!w.isNull()) {
        w->setWindowState(w->windowState() & ~Qt::WindowMinimized | Qt::WindowActive);
        w->show();
    }
}

void ActionsManager::on_windowTitleChanged()
{
    MainWindow *mw = static_cast<MainWindow*>(sender());
    m_windowActions.value(mw)->setText(mw->windowTitle());
}

ActionsManager::ActionsManager(QObject *parent) :
    QObject(parent),
    m_actions(QList<Action*>()),
    m_windowActions(QHash<QWidget*, Action*>())
{
}

bool ActionsManager::eventFilter(QObject *object, QEvent *event)
{
    if(event->type() == QEvent::WindowDeactivate) {
        minimizeAction()->setEnabled(false);
        zoomAction()->setEnabled(false);
        bringAllToFrontAction()->setEnabled(false);
        foreach(QWidget *w, QApplication::topLevelWidgets()) {
            if(w->windowType() == Qt::Window && !w->isHidden()) {
                bringAllToFrontAction()->setEnabled(true);
            }
        }

        foreach(Action *action, m_windowActions.values()) {
            QPointer<QWidget> w = action->data().value<QPointer<QWidget> >();
            if(w.isNull()) {
                m_windowActions.remove(m_windowActions.key(action));
                delete action;
                continue;
            }
            action->setChecked(false);
        }

        Action *windowAction = m_windowActions.value(QApplication::activeWindow());
        if(windowAction) {
            windowAction->setChecked(true);
        }
    }
    else if(event->type() == QEvent::WindowActivate) {
        minimizeAction()->setEnabled(true);
        zoomAction()->setEnabled(true);
        bringAllToFrontAction()->setEnabled(true);

        foreach(Action *action, m_windowActions.values()) {
            action->setChecked(false);
        }

        Action *windowAction = m_windowActions.value(QApplication::activeWindow());
        if(windowAction) {
            windowAction->setChecked(true);
        }
    }
    return QObject::eventFilter(object, event);
}

} // namespace LBGui

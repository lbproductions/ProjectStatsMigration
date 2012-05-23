#include "menubar.h"

#include "mainwindow.h"

#include <shared/action.h>
#include <shared/actionsmanager.h>

#include <QApplication>
#include <QMutex>

#include <QDebug>

namespace LBGui {

MenuBar *MenuBar::s_instance(0);

MenuBar *MenuBar::createMenuBar(MainWindow *mainWindow)
{
#ifdef Q_WS_MAC
    (void) mainWindow;
    static QMutex mutex;
    QMutexLocker locker(&mutex); (void) locker;

    if(s_instance) {
        return s_instance;
    }

    s_instance = new MenuBar(0);
    return s_instance;
#else
    return new MenuBar(mainWindow);
#endif
}



MenuBar::MenuBar(QWidget *mainWindow) :
    QMenuBar(mainWindow),
    m_menus(QHash<QString, QMenu*>()),
    m_windowMenu(0)
{
#ifdef Q_WS_MAC
    QApplication::setAttribute(Qt::AA_DontShowIconsInMenus);
#endif
}

void MenuBar::addAction(const QString &path, Action *action)
{
    menuForPath(path)->addAction(action);
}

void MenuBar::addSeparator(const QString &path)
{
    menuForPath(path)->addSeparator();
}

void MenuBar::addMenu(const QString &path, QMenu *menu)
{
    menuForPath(path)->addMenu(menu);
}

void MenuBar::addMenu(QMenu *menu)
{
    QMenuBar::addMenu(menu);
}

void MenuBar::addWindow(QWidget *w)
{
    Action *action = ActionsManager::globalInstance()->addWindowAction(w);
    if(action) {
        windowMenu()->addAction(action);
    }
}

QMenu *MenuBar::windowMenu()
{
    if(!m_windowMenu) {
        m_windowMenu = new QMenu(tr("Window"), this);
        m_windowMenu->addAction(ActionsManager::globalInstance()->minimizeAction());
        m_windowMenu->addAction(ActionsManager::globalInstance()->zoomAction());
        m_windowMenu->addSeparator();
        m_windowMenu->addAction(ActionsManager::globalInstance()->bringAllToFrontAction());
        m_windowMenu->addSeparator();
    }
    return m_windowMenu;
}

QMenu *MenuBar::helpMenu()
{
    QMenu *menu = new QMenu(QLatin1String("Help"), this);
    menu->setTitle(tr("Help"));
    return menu;
}

QMenu *MenuBar::menuForPath(const QString &path)
{
    if(m_menus.contains(path)) {
        return m_menus.value(path);
    }

    QMenu *newMenu = 0;
    int i = path.lastIndexOf('/');
    if(i == -1) {
        newMenu = new QMenu(path, this);
        QMenuBar::addMenu(newMenu);
        m_menus.insert(path, newMenu);
        return newMenu;
    }

    QString p = path;
    p.truncate(i);
    QString name = path;
    name.remove(0, i+1);
    QMenu *parentMenu = menuForPath(p);
    newMenu = new QMenu(name, parentMenu);
    parentMenu->addMenu(newMenu);
    m_menus.insert(path, newMenu);
    return newMenu;
}

} // namespace LBGui

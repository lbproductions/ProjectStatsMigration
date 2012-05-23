#ifndef LBGUI_MENUBAR_H
#define LBGUI_MENUBAR_H

#include <QMenuBar>

namespace LBGui {

class MainWindow;
class Action;

class MenuBar : public QMenuBar
{
    Q_OBJECT
public:
    static MenuBar* createMenuBar(MainWindow* mainWindow);

    void addAction(const QString &path, Action *action);

    void addSeparator(const QString &path);

    void addMenu(const QString &path, QMenu *menu);
    void addMenu(QMenu *menu);

    void addWindow(QWidget *w);
    QMenu *windowMenu();

    QMenu *helpMenu();

protected:
    MenuBar(QWidget *mainWindow = 0);

    QMenu *menuForPath(const QString &path);

    QHash<QString, QMenu*> m_menus;

    QMenu *m_windowMenu;

#ifndef Q_WS_MAC
    MainWindow *m_mainWindow; //on non MacOS each menu bar has one main window
#else
    static MenuBar *s_instance; //on MacOS we have exactly one menubar per application
#endif

};

} // namespace LBGui

#endif // LBGUI_MENUBAR_H

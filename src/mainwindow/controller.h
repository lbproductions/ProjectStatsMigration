#ifndef MAINWINDOW_CONTROLLER_H
#define MAINWINDOW_CONTROLLER_H

#include <QObject>

class MainWindow;
class Updater;
class Storage;

namespace LBDatabase {
class Entity;
}

namespace MainWindowNS {

class Actions;

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(MainWindow *mainWindow);

    MainWindow *mainWindow() const;
    Actions *actions() const;
    Storage *storage() const;

    bool close();

    void showWidget(QWidget *widget);
    void openEntityWindow(LBDatabase::Entity *entity);

public slots:
    void checkForUpdates();
    void showPreferences();

    void newGame();

signals:
    void somethingChanged();

private:
    MainWindow *m_mainWindow;
    Actions *m_actions;
    Updater *m_updater;
    Storage *m_storage;
};

} // namespace MainWindowNS

#endif // MAINWINDOW_CONTROLLER_H

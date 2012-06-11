#ifndef MAINWINDOW_CONTROLLER_H
#define MAINWINDOW_CONTROLLER_H

#include <QObject>

class MainWindow;

namespace MainWindowNS {

class Actions;

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(MainWindow *mainWindow);

    void init();

    MainWindow *mainWindow() const;
    Actions *actions();

    bool close();

public slots:
    void openStorage();

    void example();
    void showPreferences();

    void addAttribute();
    void addFunction();
    void addRelation();

    void editAttribute();
    void editFunction();
    void editRelation();

    void showWidget(QWidget *widget);

    QString getOpenFileName(const QString &windowTitle, const QString &fileDesc);

signals:
    void somethingChanged();

private:
    void openStorage(const QString &fileName);


    MainWindow *m_mainWindow;
    Actions *m_actions;
};

} // namespace MainWindowNS

#endif // MAINWINDOW_CONTROLLER_H

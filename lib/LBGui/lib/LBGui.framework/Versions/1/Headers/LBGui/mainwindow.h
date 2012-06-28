#ifndef LBGUI_MAINWINDOW_H
#define LBGUI_MAINWINDOW_H

#include <QMainWindow>

class QStackedWidget;

namespace LBGui {

class Splitter;
class Sidebar;
class SidebarChildCategorie;
class MenuBar;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(QString  title READ title WRITE setTitle)
    Q_PROPERTY(QString  settingsName READ settingsName WRITE setSettingsName)
    Q_PROPERTY(bool     saveSettings READ saveSettings WRITE setSaveSettings)
    Q_PROPERTY(QString  confirmCloseMessage READ confirmCloseMessage WRITE setConfirmCloseMessage)
    Q_PROPERTY(bool     confirmClose READ confirmClose WRITE setConfirmClose)
    Q_PROPERTY(QWidget* centralWidget READ centralWidget WRITE setCentralWidget)

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void closeEvent(QCloseEvent *event);

    QString title() const;
    void setTitle(const QString &title);
    void setWindowTitle(const QString &title);

    QString    settingsName () const;
    void    setSettingsName (const QString &settingsName);
    bool       saveSettings () const;
    void    setSaveSettings (bool saveSettings);

    QString    confirmCloseMessage () const;
    void    setConfirmCloseMessage (const QString &confirmCloseMessage);
    bool       confirmClose () const;
    void    setConfirmClose (bool confirmClose);

    QWidget   *centralWidget() const;
    void    setCentralWidget(QWidget *widget);

    void setLeftSideBar(QWidget* sidebar);
    void setLeftSideBar(Sidebar* sidebar);
    Sidebar *leftSideBar() const;

public slots:
    virtual void showCategorieWidget(::LBGui::SidebarChildCategorie*);

signals:
    void windowTitleChanged();

protected:
    QStackedWidget *centralViewStackedWidget() const;
    MenuBar *menuBar() const;

    void restoreSettings();

private:
    QString m_title;

    QString m_settingsName;
    bool    m_saveSettings;

    QString m_confirmCloseMessage;
    bool    m_confirmClose;

    bool m_leftSideBarVisible;
    bool m_rightSideBarVisible;

    Splitter*       m_verticalSplitter;
    QWidget*        m_leftSideBar;
    QStackedWidget* m_centralViewStackedWidget;
    QWidget*        m_centralWidget;
    QWidget*        m_rightSideBar;

    MenuBar*        m_menuBar;

//    ToolBar* m_toolbar;
//    Sidebar* m_sidebar;
//    ActionsManager* m_actionsManager;
//    QStackedWidget* m_stackedWidget;
//    QVBoxLayout* m_vBoxLayout;
//    Statusbar* m_statusbar;

    void _setupMainspace();

    void _saveSettings();
};

} // namespace LBGui

#endif // LBGUI_MAINWINDOW_H

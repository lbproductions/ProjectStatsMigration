#include "mainwindow.h"

#include "menubar.h"
#include "sidebar/sidebar.h"
#include "sidebar/sidebarchildcategorie.h"

#include <widgets/splitter.h>

#include <QSettings>
#include <QMessageBox>
#include <QCheckBox>
#include <QCloseEvent>
#include <QVBoxLayout>
#include <QStackedWidget>

namespace LBGui {

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),

    //properties
    m_title(QString()),
    m_settingsName(QLatin1String("MainWindow")),
    m_saveSettings(false),
    m_confirmCloseMessage(QString()),
    m_confirmClose(false),

    //widgets
    m_verticalSplitter(0),
    m_leftSideBar(0),
    m_centralWidget(0),
    m_rightSideBar(0),

    m_menuBar(MenuBar::createMenuBar(this))
{
    _setupMainspace();
}

MainWindow::~MainWindow()
{
    _saveSettings();
}

QString MainWindow::title() const
{
    return m_title;
}

void MainWindow::setTitle(const QString &title)
{
    m_title = title;
    setWindowTitle(title);
}

void MainWindow::setWindowTitle(const QString &title)
{
    QMainWindow::setWindowTitle(title);
    emit windowTitleChanged();
}

QString MainWindow::settingsName() const
{
    return m_settingsName;
}

void MainWindow::setSettingsName(const QString &settingsName)
{
    m_settingsName = settingsName;
}

bool MainWindow::saveSettings() const
{
    return m_saveSettings;
}

void MainWindow::setSaveSettings(bool saveSettings)
{
    m_saveSettings = saveSettings;
    QSettings settings;
    settings.setValue(m_settingsName+QLatin1String("/saveSettings"), saveSettings);
}

QString MainWindow::confirmCloseMessage() const
{
    return m_confirmCloseMessage;
}

void MainWindow::setConfirmCloseMessage(const QString &confirmCloseMessage)
{
    m_confirmCloseMessage = confirmCloseMessage;
}

bool MainWindow::confirmClose() const
{
    return m_confirmClose;
}

void MainWindow::setConfirmClose(bool confirmClose)
{
    m_confirmClose = confirmClose;
}

void MainWindow::_saveSettings()
{
    if(m_saveSettings) {
        QSettings settings;
        settings.setValue(m_settingsName+QLatin1String("/saveSettings"), saveSettings());
        settings.setValue(m_settingsName+QLatin1String("/geometry"), saveGeometry());
        settings.setValue(m_settingsName+QLatin1String("/windowState"), saveState());
        settings.setValue(m_settingsName+QLatin1String("/verticalSplitter/geometry"), m_verticalSplitter->saveGeometry());
        settings.setValue(m_settingsName+QLatin1String("/verticalSplitter/windowState"), m_verticalSplitter->saveState());
    }
}

void MainWindow::restoreSettings()
{
    QSettings settings;
    m_saveSettings = settings.value(m_settingsName+QLatin1String("/saveSettings"),false).toBool();
    if(m_saveSettings) {
        restoreState(settings.value(m_settingsName+QLatin1String("/windowState")).toByteArray());
        restoreGeometry(settings.value(m_settingsName+QLatin1String("/geometry")).toByteArray());
        m_verticalSplitter->restoreState(settings.value(m_settingsName+QLatin1String("/verticalSplitter/windowState")).toByteArray());
        m_verticalSplitter->restoreGeometry(settings.value(m_settingsName+QLatin1String("/verticalSplitter/geometry")).toByteArray());
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings;
    if(m_confirmClose && settings.value(m_settingsName+QLatin1String("/confirmClose"),true).toBool())
    {
        QMessageBox msg(this);
        msg.setText(m_confirmCloseMessage);
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msg.setDefaultButton(QMessageBox::Yes);
        msg.setIcon(QMessageBox::Question);

        QCheckBox dontPrompt(tr("Do not ask again"), &msg);
        dontPrompt.blockSignals(true);

        msg.addButton(&dontPrompt, QMessageBox::ActionRole);

        int ret = msg.exec();
        if(ret == QMessageBox::No) {
            event->ignore();
        }
        else {
            event->accept();
            if(dontPrompt.checkState() == Qt::Checked) {
                settings.setValue(m_settingsName+QLatin1String("/confirmClose"),false);
            }
        }
    }
    else {
        event->accept();
    }
}

QWidget *MainWindow::centralWidget() const
{
    return m_centralWidget;
}

QStackedWidget *MainWindow::centralViewStackedWidget() const
{
    return m_centralViewStackedWidget;
}

MenuBar *MainWindow::menuBar() const
{
    return m_menuBar;
}

void MainWindow::setCentralWidget(QWidget *widget)
{
    if(widget) {
        m_centralViewStackedWidget->addWidget(widget);
        m_centralViewStackedWidget->setCurrentWidget(widget);
        m_centralWidget = widget;
    }
}

void MainWindow::setLeftSideBar(QWidget *sidebar)
{
    if(m_leftSideBar) {
        m_leftSideBar->setVisible(false);
        m_leftSideBar->deleteLater();
    }

    if(sidebar) {
        m_leftSideBar = sidebar;
        m_verticalSplitter->insertWidget(0,m_leftSideBar);
        m_verticalSplitter->setStretchFactor(0, 0);
        m_verticalSplitter->setStretchFactor(1, 1);
        m_verticalSplitter->setStretchFactor(2, 0);
    }
}

void MainWindow::setLeftSideBar(Sidebar *sidebar)
{
    setLeftSideBar(static_cast<QWidget*>(sidebar));
}

Sidebar *MainWindow::leftSideBar() const
{
    return qobject_cast<Sidebar*>(m_leftSideBar);
}

void MainWindow::showCategorieWidget(SidebarChildCategorie *categorie)
{
    QWidget *w = categorie->widget();

    if(w) {
        if(!w->windowTitle().isEmpty()) {
            setWindowTitle(w->windowTitle()+ QString::fromUtf8(" \u2013 ")+m_title );
        }
        if(!categorie->icon().isNull()) {
            setWindowIcon(categorie->icon());
        }
        setCentralWidget(w);
    }
}

void MainWindow::_setupMainspace()
{
    m_verticalSplitter = new Splitter(Qt::Horizontal,this);
    m_verticalSplitter->setStyle(Splitter::MacOSStyle);

    //central widget
    QWidget *centralViewWidget = new QWidget(m_verticalSplitter);
    QVBoxLayout *centralViewLayout = new QVBoxLayout(centralViewWidget);
    centralViewLayout->setSpacing(0);
    centralViewLayout->setContentsMargins(0,0,0,0);
    m_centralViewStackedWidget = new QStackedWidget(centralViewWidget);
    centralViewLayout->addWidget(m_centralViewStackedWidget);
    m_verticalSplitter->addWidget(centralViewWidget);

    QMainWindow::setCentralWidget(m_verticalSplitter);
}

//Statusbar *MainWindow::statusBar() const
//{
//    return m_statusbar;
//}

//void MainWindow::on_sidebar_categorieChanged(Database::ChildCategorie* c)
//{
//    if(c == 0 || c->view() == 0)
//    {
//        return;
//    }

//    Views::View *view = c->view();
//    m_stackedWidget->addWidget(view);
//    m_stackedWidget->setCurrentWidget(view);
//    view->updateStatusbar();
//    if(view->windowTitle().isEmpty())
//    {
//        setWindowTitle("ProjectStats");
//    }
//    else
//    {
//        setWindowTitle(QString::fromUtf8("ProjectStats \u2013 ")+view->windowTitle());
//    }
//    setWindowIcon(view->windowIcon());
//}

//ActionsManager *MainWindow::actionsManager() const
//{
//    return m_actionsManager;
//}

} // namespace LBGui

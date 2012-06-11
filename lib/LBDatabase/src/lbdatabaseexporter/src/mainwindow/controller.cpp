#include "controller.h"

#include "actions.h"
#include "mainwindow.h"
#include "views/entitytypeview.h"

#include <LBDatabase/LBDatabase.h>
#include <LBGui/LBGui.h>

#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include <QSettings>
#include <QElapsedTimer>
#include <QDesktopServices>
#include <QFileDialog>
#include <QFileInfo>

namespace MainWindowNS {

Controller::Controller(MainWindow *mainWindow) :
    QObject(mainWindow),
    m_mainWindow(mainWindow),
    m_actions(new Actions(this))
{
}

void Controller::init()
{
    QSettings settings;
    QString fileName = settings.value("controller/lastChosenStorage").toString();
    QFile lastStorage(fileName);
    if(lastStorage.exists()) {
        openStorage(fileName);
    }
    else {
        openStorage();
    }
}

MainWindow *Controller::mainWindow() const
{
    return m_mainWindow;
}

Actions *Controller::actions()
{
    return m_actions;
}

bool Controller::close()
{
    //somehow confirm the closing of the main window
    return true;
}

void Controller::openStorage()
{
    openStorage(getOpenFileName(tr("Choose Storage"), "*.lbstorage"));
}

void Controller::openStorage(const QString &fileName)
{
    QSettings settings;
    settings.setValue("controller/lastChosenStorage", fileName);

    LBDatabase::Storage *storage = new LBDatabase::Storage(m_mainWindow);

    QElapsedTimer timer;
    timer.start();
//    LBGui::AutosaveFile *autosaveFile = LBGui::AutosaveFile::instance(fileName);
//    storage->setDriver(new LBDatabase::LocalStorageDriver(autosaveFile->copyFileName(),storage));
    storage->setDriver(new LBDatabase::LocalStorageDriver(fileName,storage));
    storage->open();
    qDebug() << "Opening the storage" << fileName << "took "+QString::number(timer.elapsed())+"ms.";
    m_mainWindow->setStorage(storage);
}

void Controller::example()
{
    QMessageBox msg;
    msg.setText("Example");
    msg.exec();

    emit somethingChanged();
}

void Controller::showPreferences()
{
    LBGui::PreferencesWindow *window = new LBGui::PreferencesWindow;

    window->show();
}

void Controller::addAttribute()
{
    static_cast<MainWindowNS::EntityTypeView *>(m_mainWindow->centralWidget())->addAttribute();
}

void Controller::addFunction()
{
    static_cast<MainWindowNS::EntityTypeView *>(m_mainWindow->centralWidget())->addFunction();
}

void Controller::addRelation()
{
    static_cast<MainWindowNS::EntityTypeView *>(m_mainWindow->centralWidget())->addRelation();
}

void Controller::editAttribute()
{
    static_cast<MainWindowNS::EntityTypeView *>(m_mainWindow->centralWidget())->editAttribute();
}

void Controller::editFunction()
{
    static_cast<MainWindowNS::EntityTypeView *>(m_mainWindow->centralWidget())->editFunction();
}

void Controller::editRelation()
{
    static_cast<MainWindowNS::EntityTypeView *>(m_mainWindow->centralWidget())->editRelation();
}

void Controller::showWidget(QWidget *widget)
{
    m_mainWindow->setCentralWidget(widget);
    emit somethingChanged();
}

QString Controller::getOpenFileName(const QString &windowTitle, const QString &fileDesc)
{
    QSettings settings;
    QString lastOpenFolder = settings.value("lastOpenFolder",
                                            QDesktopServices::storageLocation(QDesktopServices::HomeLocation)).toString();
    QString fileName = QFileDialog::getOpenFileName(0,windowTitle, lastOpenFolder, fileDesc);

    QFile file(fileName);

    if(file.exists() || file.open(QIODevice::WriteOnly)) {
        settings.setValue("lastOpenFolder",QFileInfo(file).absolutePath());
        return file.fileName();
    }

    return QString();
}

} // namespace MainWindowNS

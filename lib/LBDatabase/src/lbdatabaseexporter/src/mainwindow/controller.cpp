#include "controller.h"

#include "actions.h"
#include "mainwindow.h"
#include "views/entitytypeview.h"

#include "../cppexporter.h"

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

    m_storage = new LBDatabase::Storage(m_mainWindow);

    QElapsedTimer timer;
    timer.start();
//    LBGui::AutosaveFile *autosaveFile = LBGui::AutosaveFile::instance(fileName);
//    storage->setDriver(new LBDatabase::LocalStorageDriver(autosaveFile->copyFileName(),storage));
    m_storage->setDriver(new LBDatabase::LocalStorageDriver(fileName,m_storage));
    m_storage->open();
    qDebug() << "Opening the storage" << fileName << "took "+QString::number(timer.elapsed())+"ms.";
    m_mainWindow->setStorage(m_storage);
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

void Controller::exportSource()
{
    exportSource(static_cast<MainWindowNS::EntityTypeView *>(m_mainWindow->centralWidget())->sourceLocation());
}

void Controller::exportSource(const QString &location)
{
    QFile f(location);
    if(!f.exists() || !QFileInfo(f).isDir()) {
        QMessageBox msg(m_mainWindow);
        msg.setText("The C++ source for the storage could not be exported.");
        msg.setInformativeText("The chosen location is no writable directory.");
        msg.setIcon(QMessageBox::Critical);
        msg.setModal(true);
        msg.exec();
        return;
    }

    LBDatabase::CppExporter exporter;
    exporter.setDirectory(location);
    exporter.setStorage(m_storage);
    exporter.exportCpp();

    QMessageBox msg(m_mainWindow);
    msg.setText("Successfully exported C++ source to:");
    msg.setInformativeText(location);
    msg.setIcon(QMessageBox::Information);
    msg.setModal(true);
    msg.exec();
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

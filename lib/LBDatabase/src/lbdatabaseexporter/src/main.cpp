#include <QtGui/QApplication>

#include <LBDatabase/LBDatabase.h>

#include "mainwindow/mainwindow.h"
#include "misc/logger.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Logger::init();

    LBGUI_INIT_RESOURCES;

    QApplication::setApplicationName(QLatin1String("LB Example Project"));
    QApplication::setOrganizationName(QLatin1String("LBProductions"));

    MainWindow window;
    window.show();

    LBDatabase::Storage *storage = new LBDatabase::Storage(&window);

    storage->setDriver(
                new LBDatabase::LocalStorageDriver(
                    "/Users/niklas/Library/Application Support/LBProductions/ProjectStats/storage.lbstorage",
                    storage)
                );

    storage->open();
    window.setStorage(storage);

    return a.exec();
}

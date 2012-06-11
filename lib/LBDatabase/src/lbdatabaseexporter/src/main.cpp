#include <QtGui/QApplication>

#include <LBDatabase/LBDatabase.h>

#include "mainwindow/controller.h"
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
    window.controller()->init();

    return a.exec();
}

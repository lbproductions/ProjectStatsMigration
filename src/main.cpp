#include <QApplication>

#include "mainwindow/mainwindow.h"
#include "misc/logger.h"
#ifdef Q_OS_MAC
#   include "misc/cocoainitializer.h"
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#ifdef Q_OS_MAC
    CocoaInitializer cocoaInitializer;
    Q_UNUSED(cocoaInitializer)
#endif

    Logger::init();

    LBGUI_INIT_RESOURCES;

    QApplication::setApplicationName(QLatin1String("ProjectStats"));
    QApplication::setOrganizationName(QLatin1String("LBProductions"));

    MainWindow window;
    window.show();

    return a.exec();
}

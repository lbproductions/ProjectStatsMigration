QT       += core gui sql

TARGET = ProjectStats
TEMPLATE = app

VERSION = 0.1
DEPLOY_DIR = $$OUT_PWD/../deploy
DESTDIR = $$OUT_PWD/../
OBJECTS_DIR = $$OUT_PWD/../build/
MYICON = $$PWD/resources/icon/ApplicationIcon.icns
APPCASTURL = http://dl.dropbox.com/u/140012/$$TARGET

DEFINES +=  'APPCASTURL=\'\"$$APPCASTURL\"\''

INCLUDEPATH += $$PWD/../lib/LBDatabase/include
INCLUDEPATH += $$PWD/../lib/LBGui/include

CXXFLAGS+=-Wpedantic

# add a build command
defineReplace( nc  ) {
    return( $$escape_expand(\\n\\t)$$1    )
}
# add a silent build command
defineReplace( snc ) {
    return( $$escape_expand(\\n\\t)"@"$$1 )
}
# add end of line
defineReplace( nl  ) {
    return( $$escape_expand(\\n)         )
}

macx {
    HEADERS  += \
        misc/sparkleupdater.h \
        misc/cocoainitializer.h
    LIBS += \
        -F$$PWD/../frameworks/ \
        -F$$PWD/../lib/LBDatabase/frameworks/ \
        -framework AppKit \
        -framework Sparkle \
        -framework QxtCore \
        -framework QxtNetwork \
        -framework QxtWeb

    INCLUDEPATH += $$PWD/../frameworks/Sparkle.framework/Headers

    CONFIG += qxt
    QXT     += core web network
    QXT_DIR = $${PWD}/../lib/LBDatabase/lib/libqxt-0.6.2
    LIBS += -F$${QXT_DIR}/lib
    INCLUDEPATH += $${QXT_DIR}/include

    OBJECTIVE_SOURCES += \
        misc/sparkleupdater.mm \
        misc/cocoainitializer.mm

    LIBS += -L$$OUT_PWD/../lib/LBDatabase/
    LIBS += -llbdatabase

    LIBS += -L$$OUT_PWD/../lib/LBGui/
    LIBS += -llbgui

    copyFrameworks.target = frameworks
    copyFrameworks.commands += rm -Rf $$DESTDIR/$${TARGET}.app/Contents/Frameworks/
    copyFrameworks.commands += $$snc( mkdir -p $$DESTDIR/$${TARGET}.app/Contents/Frameworks/ )
    copyFrameworks.commands += $$snc( cp -R $$PWD/../lib/LBDatabase/frameworks/* $$DESTDIR/$${TARGET}.app/Contents/Frameworks/ )
    copyFrameworks.commands += $$snc( cp -R $$PWD/../frameworks/* $$DESTDIR/$${TARGET}.app/Contents/Frameworks/ )
    copyFrameworks.commands += $$snc( cp -R $$QMAKE_LIBDIR_QT/QtCore.framework $$DESTDIR/$${TARGET}.app/Contents/Frameworks/ )
    copyFrameworks.commands += $$snc( cp -R $$QMAKE_LIBDIR_QT/QtNetwork.framework $$DESTDIR/$${TARGET}.app/Contents/Frameworks/ )

    copyDylibs.target = dylibs
    copyDylibs.commands += mkdir -p $$DESTDIR/$${TARGET}.app/Contents/MacOS/
    copyDylibs.commands += $$snc(   cp $$DESTDIR/lib/LBDatabase/liblbdatabase.1.0.0.dylib $$DESTDIR/$${TARGET}.app/Contents/MacOS/ )
    copyDylibs.commands += $$snc(   cp $$DESTDIR/lib/LBDatabase/liblbdatabase.1.dylib $$DESTDIR/$${TARGET}.app/Contents/MacOS/ )
    copyDylibs.commands += $$snc(   cp $$DESTDIR/lib/LBGui/liblbgui.1.0.0.dylib $$DESTDIR/$${TARGET}.app/Contents/MacOS/ )
    copyDylibs.commands += $$snc(   cp $$DESTDIR/lib/LBGui/liblbgui.1.dylib $$DESTDIR/$${TARGET}.app/Contents/MacOS/ )

    QMAKE_POST_LINK = install_name_tool -id @executable_path/liblbdatabase.1.dylib $$DESTDIR/$${TARGET}.app/Contents/MacOS/liblbdatabase.1.dylib &&
    QMAKE_POST_LINK += install_name_tool -id @executable_path/liblbgui.1.dylib $$DESTDIR/$${TARGET}.app/Contents/MacOS/liblbgui.1.dylib &&
    QMAKE_POST_LINK += install_name_tool -change liblbdatabase.1.dylib @executable_path/liblbdatabase.1.dylib $$DESTDIR/$${TARGET}.app/Contents/MacOS/$$TARGET &&
    QMAKE_POST_LINK += install_name_tool -change liblbgui.1.dylib @executable_path/liblbgui.1.dylib $$DESTDIR/$${TARGET}.app/Contents/MacOS/$$TARGET &&
    QMAKE_POST_LINK += install_name_tool -change liblbdatabase.1.dylib @executable_path/liblbgui.1.dylib $$DESTDIR/$${TARGET}.app/Contents/MacOS/liblbgui.1.dylib &&

    QMAKE_POST_LINK += install_name_tool -id @executable_path/../Frameworks/QxtCore.framework/QxtCore $$DESTDIR/$${TARGET}.app/Contents/Frameworks/QxtCore.framework/QxtCore &&
    QMAKE_POST_LINK += install_name_tool -change QxtCore.framework/Versions/0/QxtCore @executable_path/../Frameworks/QxtCore.framework/QxtCore $$DESTDIR/$${TARGET}.app/Contents/MacOS/$$TARGET &&
    QMAKE_POST_LINK += install_name_tool -id @executable_path/../Frameworks/QxtWeb.framework/QxtWeb $$DESTDIR/$${TARGET}.app/Contents/Frameworks/QxtWeb.framework/QxtWeb &&
    QMAKE_POST_LINK += install_name_tool -change QxtWeb.framework/Versions/0/QxtWeb @executable_path/../Frameworks/QxtWeb.framework/QxtWeb $$DESTDIR/$${TARGET}.app/Contents/MacOS/$$TARGET &&
    QMAKE_POST_LINK += install_name_tool -id @executable_path/../Frameworks/QxtNetwork.framework/QxtNetwork $$DESTDIR/$${TARGET}.app/Contents/Frameworks/QxtNetwork.framework/QxtNetwork &&
    QMAKE_POST_LINK += install_name_tool -change QxtNetwork.framework/Versions/0/QxtNetwork @executable_path/../Frameworks/QxtNetwork.framework/QxtNetwork $$DESTDIR/$${TARGET}.app/Contents/MacOS/$$TARGET &&
    QMAKE_POST_LINK += install_name_tool -change QxtCore.framework/Versions/0/QxtCore @executable_path/../Frameworks/QxtCore.framework/QxtCore $$DESTDIR/$${TARGET}.app/Contents/Frameworks/QxtNetwork.framework/QxtNetwork &&
    QMAKE_POST_LINK += install_name_tool -change QxtCore.framework/Versions/0/QxtCore @executable_path/../Frameworks/QxtCore.framework/QxtCore $$DESTDIR/$${TARGET}.app/Contents/Frameworks/QxtWeb.framework/QxtWeb &&
    QMAKE_POST_LINK += install_name_tool -change QxtNetwork.framework/Versions/0/QxtNetwork @executable_path/../Frameworks/QxtNetwork.framework/QxtNetwork $$DESTDIR/$${TARGET}.app/Contents/Frameworks/QxtWeb.framework/QxtWeb &&
    QMAKE_POST_LINK += install_name_tool -change QxtCore.framework/Versions/0/QxtCore @executable_path/../Frameworks/QxtCore.framework/QxtCore $$DESTDIR/$${TARGET}.app/Contents/MacOS/liblbdatabase.1.dylib &&
    QMAKE_POST_LINK += install_name_tool -change QxtNetwork.framework/Versions/0/QxtNetwork @executable_path/../Frameworks/QxtNetwork.framework/QxtNetwork $$DESTDIR/$${TARGET}.app/Contents/MacOS/liblbdatabase.1.dylib &&
    QMAKE_POST_LINK += install_name_tool -change QxtWeb.framework/Versions/0/QxtWeb @executable_path/../Frameworks/QxtWeb.framework/QxtWeb $$DESTDIR/$${TARGET}.app/Contents/MacOS/liblbdatabase.1.dylib &&

    QMAKE_POST_LINK += install_name_tool -id @executable_path/../Frameworks/QtCore.framework/QtCore $$DESTDIR/$${TARGET}.app/Contents/Frameworks/QtCore.framework/QtCore &&
    QMAKE_POST_LINK += install_name_tool -change QtCore.framework/Versions/4/QtCore @executable_path/../Frameworks/QtCore.framework/QtCore $$DESTDIR/$${TARGET}.app/Contents/MacOS/$$TARGET &&

    QMAKE_POST_LINK += install_name_tool -id @executable_path/../Frameworks/QtNetwork.framework/QtNetwork $$DESTDIR/$${TARGET}.app/Contents/Frameworks/QtNetwork.framework/QtNetwork &&
    QMAKE_POST_LINK += install_name_tool -change QtNetwork.framework/Versions/4/QtNetwork @executable_path/../Frameworks/QtNetwork.framework/QtCore $$DESTDIR/$${TARGET}.app/Contents/MacOS/$$TARGET


    QMAKE_EXTRA_TARGETS += copyFrameworks copyDylibs
    PRE_TARGETDEPS += frameworks dylibs

     CONFIG(release, debug|release) {
        QMAKE_POST_LINK += && rm -Rf $$DESTDIR/deploy && $$PWD/../util/deployment/mac/deploy.sh $$PWD $$OUT_PWD/../ $$DEPLOY_DIR $$MYICON $$TARGET $$APPCASTURL && \
                             rm -Rf $$DESTDIR/deploy/Contents
    }
}

SOURCES += main.cpp \
    mainwindow/mainwindow.cpp \
    mainwindow/actions.cpp \
    mainwindow/controller.cpp \
    mainwindow/sidebar.cpp \
    misc/logger.cpp \
    preferences/updaterpreferences.cpp \
    mainwindow/views/listview.cpp \
    model/round.cpp \
    model/player.cpp \
    model/place.cpp \
    model/livedrink.cpp \
    model/game.cpp \
    model/drink.cpp \
    model/projectstatsstorage.cpp \
    model/livegame.cpp \
    model/schmeisserei.cpp \
    model/rule.cpp \
    model/playercalculator.cpp \
    model/placecalculator.cpp \
    model/livegamecalculator.cpp \
    model/gamecalculator.cpp \
    model/drinkcalculator.cpp \
    model/doppelkopfround.cpp \
    model/doppelkopflivegame.cpp \
    model/category.cpp \
    mainwindow/views/contexttreeview.cpp \
    wizards/newgame/newgamewizard.cpp \
    wizards/newgame/livegamegeneraloptionswidget.cpp \
    wizards/newgame/livedokogameoptionswidget.cpp \
    wizards/newgame/chooseunfinishedgamedialog.cpp \
    widgets/placescombobox.cpp \
    widgets/playerslistwidget.cpp \
    windows/livegame/livegamewindow.cpp \
    widgets/graphs/livegamegraphview.cpp \
    widgets/graphs/items/livegameplayerpointsgraph.cpp \
    widgets/graphs/items/livegamecoordinatesystem.cpp \
    widgets/graphs/items/graphpoint.cpp \
    widgets/graphs/items/graph.cpp \
    widgets/graphs/items/dokolivegameplayerpointsgraph.cpp \
    widgets/graphs/items/dokolivegamecoordinatesystem.cpp \
    widgets/graphs/items/dokographpoint.cpp \
    widgets/graphs/items/coordinatesystem.cpp \
    widgets/graphs/items/abstractitem.cpp \
    widgets/graphs/graphview.cpp \
    widgets/graphs/dokolivegamegraphview.cpp

HEADERS  += \
    mainwindow/mainwindow.h \
    mainwindow/actions.h \
    mainwindow/controller.h \
    mainwindow/sidebar.h \
    misc/logger.h \
    misc/updater.h \
    preferences/updaterpreferences.h \
    mainwindow/views/listview.h \
    model/round.h \
    model/player.h \
    model/place.h \
    model/livedrink.h \
    model/game.h \
    model/drink.h \
    model/projectstatsstorage.h \
    model/livegame.h \
    model/schmeisserei.h \
    model/rule.h \
    model/playercalculator.h \
    model/placecalculator.h \
    model/livegamecalculator.h \
    model/gamecalculator.h \
    model/drinkcalculator.h \
    model/doppelkopfround.h \
    model/doppelkopflivegame.h \
    model/category.h \
    mainwindow/views/contexttreeview.h \
    wizards/newgame/newgamewizard.h \
    wizards/newgame/livegamegeneraloptionswidget.h \
    wizards/newgame/livedokogameoptionswidget.h \
    wizards/newgame/chooseunfinishedgamedialog.h \
    widgets/placescombobox.h \
    widgets/playerslistwidget.h \
    windows/livegame/livegamewindow.h \
    widgets/graphs/roundgraphview.h \
    widgets/graphs/livegamegraphview.h \
    widgets/graphs/items/playergraph.h \
    widgets/graphs/items/livegameplayerpointsgraph.h \
    widgets/graphs/items/livegamecoordinatesystem.h \
    widgets/graphs/items/graphpoint.h \
    widgets/graphs/items/graph.h \
    widgets/graphs/items/dokolivegameplayerpointsgraph.h \
    widgets/graphs/items/dokolivegamecoordinatesystem.h \
    widgets/graphs/items/dokographpoint.h \
    widgets/graphs/items/coordinatesystem.h \
    widgets/graphs/items/abstractitem.h \
    widgets/graphs/graphview.h \
    widgets/graphs/dokolivegamegraphview.h

RESOURCES += \
    resources/resources.qrc

FORMS += \
    wizards/newgame/livesummarywidget.ui \
    wizards/newgame/livegamegeneraloptionswidget.ui \
    wizards/newgame/livedokogameoptionswidget.ui \
    wizards/newgame/dokolivegamegroupbox.ui \
    wizards/newgame/chooseunfinishedgamedialog.ui

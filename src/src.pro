QT       += core gui sql

<<<<<<< HEAD
contains(QT, ^5) {
    QT += widgets
=======
contains(QT_VERSION, ^5) {
QT += widgets
>>>>>>> c66e475ac5567d26ecc89da91ede091aa00d9884
}

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

macx {
    HEADERS  += \
        misc/sparkleupdater.h \
        misc/cocoainitializer.h

    LIBS += \
        -F$$PWD/../frameworks/ \
        -F$$PWD/../lib/LBDatabase/lib/ \
        -F$$PWD/../lib/LBGui/lib/ \
        -F$$PWD/../lib/libqxt-0.6.2/lib/ \
        -framework AppKit \
        -framework Sparkle \
        -framework LBGui \
        -framework LBDatabase

    INCLUDEPATH += $$PWD/../frameworks/Sparkle.framework/Headers

    OBJECTIVE_SOURCES += \
        misc/sparkleupdater.mm \
        misc/cocoainitializer.mm

    FRAMEWORKSPATH = $$DESTDIR/$${TARGET}.app/Contents/Frameworks/
    TARGETEXECUTABLE = $$DESTDIR/$${TARGET}.app/Contents/MacOS/$$TARGET


    defineReplace( nc  ) {
        return( $$escape_expand(\\n\\t)$$1    )
    }
    defineReplace( copyFramework ) {
        return( $$nc( cp -R -p  $$1 $$FRAMEWORKSPATH ) )
    }
    defineReplace( installNameToolOnTarget  ) {
        return( $$nc( install_name_tool -change $${1}.framework/$${1} @loader_path/../Framworks/$${1}.framework/$${1} $$TARGETEXECUTABLE ) )
    }
    defineReplace( installNameToolOnFramework  ) {
        return( $$nc( install_name_tool -change $${1}.framework/$${1} @loader_path/../Framworks/$${1}.framework/$${1} $$FRAMEWORKSPATH/$${2}.framework/$${2} ) )
    }
    COPY_FRAMEWORKS.target = copyFrameworks
    COPY_FRAMEWORKS.commands += $$nc( rm -Rf $$DESTDIR/$${TARGET}.app/Contents/Frameworks/ )
    COPY_FRAMEWORKS.commands += $$nc( mkdir -p $$DESTDIR/$${TARGET}.app/Contents/Frameworks/ )
    COPY_FRAMEWORKS.commands += $$copyFramework($$PWD/../lib/LBDatabase/lib/LBDatabase.framework )
    COPY_FRAMEWORKS.commands += $$copyFramework($$PWD/../lib/LBGui/lib/LBGui.framework )
    COPY_FRAMEWORKS.commands += $$copyFramework($$PWD/../frameworks/Sparkle.framework )
    COPY_FRAMEWORKS.commands += $$copyFramework($$PWD/../lib/libqxt-0.6.2/lib/QxtCore.framework )
    COPY_FRAMEWORKS.commands += $$copyFramework($$PWD/../lib/libqxt-0.6.2/lib/QxtWeb.framework )
    COPY_FRAMEWORKS.commands += $$copyFramework($$PWD/../lib/libqxt-0.6.2/lib/QxtGui.framework )
    COPY_FRAMEWORKS.commands += $$copyFramework($$PWD/../lib/libqxt-0.6.2/lib/QxtNetwork.framework )
    COPY_FRAMEWORKS.commands += $$copyFramework($$QMAKE_LIBDIR_QT/QtCore.framework )
    COPY_FRAMEWORKS.commands += $$copyFramework($$QMAKE_LIBDIR_QT/QtNetwork.framework )
    COPY_FRAMEWORKS.commands += $$copyFramework($$QMAKE_LIBDIR_QT/QtGui.framework )

    QMAKE_POST_LINK += $$installNameToolOnTarget(LBDatabase)
    QMAKE_POST_LINK += $$installNameToolOnTarget(LBGui)
    QMAKE_POST_LINK += $$installNameToolOnTarget(QxtCore)
    QMAKE_POST_LINK += $$installNameToolOnTarget(QxtNetwork)
    QMAKE_POST_LINK += $$installNameToolOnTarget(QxtWeb)
    QMAKE_POST_LINK += $$installNameToolOnTarget(QxtGui)
    QMAKE_POST_LINK += $$installNameToolOnTarget(QtCore)
    QMAKE_POST_LINK += $$installNameToolOnTarget(QtGui)
    QMAKE_POST_LINK += $$installNameToolOnTarget(QtNetwork)

#    QMAKE_POST_LINK += install_name_tool -id @executable_path/../Frameworks/QxtCore.framework/QxtCore $$DESTDIR/$${TARGET}.app/Contents/Frameworks/QxtCore.framework/QxtCore &&
#    QMAKE_POST_LINK += install_name_tool -change QxtCore.framework/Versions/0/QxtCore @executable_path/../Frameworks/QxtCore.framework/QxtCore $$DESTDIR/$${TARGET}.app/Contents/MacOS/$$TARGET &&
#    QMAKE_POST_LINK += install_name_tool -id @executable_path/../Frameworks/QxtWeb.framework/QxtWeb $$DESTDIR/$${TARGET}.app/Contents/Frameworks/QxtWeb.framework/QxtWeb &&
#    QMAKE_POST_LINK += install_name_tool -change QxtWeb.framework/Versions/0/QxtWeb @executable_path/../Frameworks/QxtWeb.framework/QxtWeb $$DESTDIR/$${TARGET}.app/Contents/MacOS/$$TARGET &&
#    QMAKE_POST_LINK += install_name_tool -id @executable_path/../Frameworks/QxtNetwork.framework/QxtNetwork $$DESTDIR/$${TARGET}.app/Contents/Frameworks/QxtNetwork.framework/QxtNetwork &&
#    QMAKE_POST_LINK += install_name_tool -change QxtNetwork.framework/Versions/0/QxtNetwork @executable_path/../Frameworks/QxtNetwork.framework/QxtNetwork $$DESTDIR/$${TARGET}.app/Contents/MacOS/$$TARGET &&
#    QMAKE_POST_LINK += install_name_tool -change QxtCore.framework/Versions/0/QxtCore @executable_path/../Frameworks/QxtCore.framework/QxtCore $$DESTDIR/$${TARGET}.app/Contents/Frameworks/QxtNetwork.framework/QxtNetwork &&
#    QMAKE_POST_LINK += install_name_tool -change QxtCore.framework/Versions/0/QxtCore @executable_path/../Frameworks/QxtCore.framework/QxtCore $$DESTDIR/$${TARGET}.app/Contents/Frameworks/QxtWeb.framework/QxtWeb &&
#    QMAKE_POST_LINK += install_name_tool -change QxtNetwork.framework/Versions/0/QxtNetwork @executable_path/../Frameworks/QxtNetwork.framework/QxtNetwork $$DESTDIR/$${TARGET}.app/Contents/Frameworks/QxtWeb.framework/QxtWeb &&

#    QMAKE_POST_LINK += install_name_tool -id @executable_path/../Frameworks/QtCore.framework/QtCore $$DESTDIR/$${TARGET}.app/Contents/Frameworks/QtCore.framework/QtCore &&
#    QMAKE_POST_LINK += install_name_tool -change QtCore.framework/Versions/4/QtCore @executable_path/../Frameworks/QtCore.framework/QtCore $$DESTDIR/$${TARGET}.app/Contents/MacOS/$$TARGET &&

#    QMAKE_POST_LINK += install_name_tool -id @executable_path/../Frameworks/QtNetwork.framework/QtNetwork $$DESTDIR/$${TARGET}.app/Contents/Frameworks/QtNetwork.framework/QtNetwork &&
#    QMAKE_POST_LINK += install_name_tool -change QtNetwork.framework/Versions/4/QtNetwork @executable_path/../Frameworks/QtNetwork.framework/QtCore $$DESTDIR/$${TARGET}.app/Contents/MacOS/$$TARGET


    QMAKE_EXTRA_TARGETS += COPY_FRAMEWORKS
    PRE_TARGETDEPS += copyFrameworks

     CONFIG(release, debug|release) {
        QMAKE_POST_LINK += && rm -Rf $$DESTDIR/deploy && $$PWD/../util/deployment/mac/deploy.sh $$PWD $$OUT_PWD/../ $$DEPLOY_DIR $$MYICON $$TARGET $$APPCASTURL && \
                             rm -Rf $$DESTDIR/deploy/Contents
    }
}

win32 {
SOURCES +=  \
    misc/winsparkleupdater.cpp

HEADERS +=  \
    misc/winsparkleupdater.h

CONFIG += windows

LIBS += -L$$OUT_PWD/../lib/LBDatabase -llbdatabase \
        -L$$OUT_PWD/../lib/LBGui -llbgui \
        -L$$PWD/../frameworks/WinSparkle-0.3 -lWinSparkle

DDIR = $$DESTDIR
DDIR ~= s,/,\\,g
PWDDIR = $$PWD
PWDDIR ~= s,/,\\,g

     CONFIG(release, debug|release) {
        QMAKE_POST_LINK += $$PWD/../util/deployment/win/deploy.bat "$$DDIR" "$${TARGET}.exe" $$PWDDIR
    }
QMAKE_LFLAGS = -Wl,-enable-auto-import
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
    model/storage.cpp \
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
    widgets/graphs/dokolivegamegraphview.cpp \
    model/roundcalculator.cpp \
    model/doppelkopfroundcalculator.cpp \
    model/schmeissereiencontext.cpp \
    model/rulescontext.cpp \
    model/roundscontext.cpp \
    model/playerscontext.cpp \
    model/placescontext.cpp \
    model/livedrinkscontext.cpp \
    model/gamescontext.cpp \
    model/drinkscontext.cpp \
    model/categoriescontext.cpp \
    model/skatround.cpp \
    model/skatlivegame.cpp \
    windows/livegame/doppelkopf/dokolivegamewindow.cpp \
    windows/livegame/doppelkopf/centralwidget.cpp \
    windows/livegame/doppelkopf/pointstable.cpp \
    windows/livegame/doppelkopf/pointstableitem.cpp \
    windows/livegame/doppelkopf/pointstabledelegate.cpp \
    windows/livegame/doppelkopf/totalpointstable.cpp \
    windows/livegame/doppelkopf/newrounddialog.cpp \
    widgets/playerscombobox.cpp \
    model/doppelkopflivegamecalculator.cpp \
    windows/livegame/doppelkopf/newschmeissereidialog.cpp \
    windows/livegame/sidebarpage.cpp \
    windows/livegame/livegamesidebar.cpp \
    windows/livegame/drinkssidebarpage.cpp \
    windows/livegame/playerdrinksgroupbox.cpp \
    windows/livegame/doppelkopf/statisticssidebar.cpp \
    windows/livegame/doppelkopf/statisticsgeneralpage.cpp \
    windows/livegame/adddrinkwidget.cpp

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
    model/storage.h \
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
    widgets/graphs/dokolivegamegraphview.h \
    model/roundcalculator.h \
    model/doppelkopfroundcalculator.h \
    model/schmeissereiencontext.h \
    model/rulescontext.h \
    model/roundscontext.h \
    model/playerscontext.h \
    model/placescontext.h \
    model/livedrinkscontext.h \
    model/gamescontext.h \
    model/drinkscontext.h \
    model/categoriescontext.h \
    model/skatround.h \
    model/skatlivegame.h \
    windows/livegame/doppelkopf/dokolivegamewindow.h \
    windows/livegame/doppelkopf/centralwidget.h \
    windows/livegame/doppelkopf/pointstable.h \
    windows/livegame/doppelkopf/pointstableitem.h \
    windows/livegame/doppelkopf/pointstabledelegate.h \
    windows/livegame/doppelkopf/totalpointstable.h \
    windows/livegame/doppelkopf/newrounddialog.h \
    widgets/playerscombobox.h \
    model/doppelkopflivegamecalculator.h \
    windows/livegame/doppelkopf/newschmeissereidialog.h \
    windows/livegame/sidebarpage.h \
    windows/livegame/livegamesidebar.h \
    windows/livegame/drinkssidebarpage.h \
    windows/livegame/playerdrinksgroupbox.h \
    windows/livegame/doppelkopf/statisticssidebar.h \
    windows/livegame/doppelkopf/statisticsgeneralpage.h \
    windows/livegame/adddrinkwidget.h

RESOURCES += \
    resources/resources.qrc \
    resources/drinks.qrc

FORMS += \
    wizards/newgame/livesummarywidget.ui \
    wizards/newgame/livegamegeneraloptionswidget.ui \
    wizards/newgame/livedokogameoptionswidget.ui \
    wizards/newgame/dokolivegamegroupbox.ui \
    wizards/newgame/chooseunfinishedgamedialog.ui \
    windows/livegame/doppelkopf/newrounddialog.ui \
    windows/livegame/doppelkopf/newschmeissereidialog.ui \
    windows/livegame/adddrinkwidget.ui

OTHER_FILES += \
    resources/stylesheets/pointstable.css \
    resources/stylesheets/livegamesidebar.css

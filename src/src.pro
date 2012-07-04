QT       += core gui sql

contains(QT_VERSION, ^5) {
    QT += widgets
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

CONFIG += qxt
QXT = core widgets network web

macx {
    HEADERS  += \
        misc/sparkleupdater.h \
        misc/cocoainitializer.h

    LIBS += \
        -F$$PWD/../frameworks/ \
        -F$$PWD/../lib/LBDatabase/lib/ \
        -F$$PWD/../lib/LBGui/lib/ \
        -framework AppKit \
        -framework Sparkle \
        -framework LBGui \
        -framework LBDatabase

    INCLUDEPATH += $$PWD/../frameworks/Sparkle.framework/Headers

    OBJECTIVE_SOURCES += \
        misc/sparkleupdater.mm \
        misc/cocoainitializer.mm

    APPCONTENTSPATH = $$DESTDIR/$${TARGET}.app/Contents
    PLUGINSPATH = $$APPCONTENTSPATH/PlugIns
    FRAMEWORKSPATH = $$APPCONTENTSPATH/Frameworks
    TARGETEXECUTABLE = $$APPCONTENTSPATH/MacOS/$$TARGET
    RESOURCESPATH = $$APPCONTENTSPATH/Resources

    QXT_DIR = $$PWD/../lib/libqxt

    defineReplace( nc  ) {
        return( $$escape_expand(\\n\\t)$$1    )
    }

    ######### Mac Debug ##########

    CONFIG(debug, debug|release) {
        defineReplace( symlinkFramework ) {
            return( $$nc( rm -Rf $$FRAMEWORKSPATH/$$2 && mkdir -p $$FRAMEWORKSPATH/$$2 && rm -R $$FRAMEWORKSPATH/$$2 && ln -s $$1/$$2 $$FRAMEWORKSPATH/$$2 ) )
        }
        defineReplace( installNameToolOnTarget  ) {
            return( $$nc( install_name_tool -change $${1}.framework/Versions/0/$${1} @executable_path/../Frameworks/$${1}.framework/$${1} $$TARGETEXECUTABLE ) )
        }

        QMAKE_POST_LINK += $$symlinkFramework($$PWD/../lib/LBDatabase/lib, LBDatabase.framework/LBDatabase)
        QMAKE_POST_LINK += $$symlinkFramework($$PWD/../lib/LBGui/lib, LBGui.framework/LBGui)
        QMAKE_POST_LINK += $$nc( install_name_tool -change @loader_path/../Frameworks/Sparkle.framework/Versions/A/Sparkle $$PWD/../frameworks/Sparkle.framework/Sparkle $$TARGETEXECUTABLE )
        QMAKE_POST_LINK += $$symlinkFramework($$QXT_DIR/lib, QxtCore.framework/QxtCore)
        QMAKE_POST_LINK += $$symlinkFramework($$QXT_DIR/lib, QxtNetwork.framework/QxtNetwork)
        QMAKE_POST_LINK += $$symlinkFramework($$QXT_DIR/lib, QxtWeb.framework/QxtWeb)
        QMAKE_POST_LINK += $$symlinkFramework($$QXT_DIR/lib, QxtGui.framework/QxtGui)

        QMAKE_POST_LINK += $$symlinkFramework($$QMAKE_LIBDIR_QT, QtCore.framework/Versions/4/QtCore )
        QMAKE_POST_LINK += $$symlinkFramework($$QMAKE_LIBDIR_QT, QtGui.framework/Versions/4/QtGui )
        QMAKE_POST_LINK += $$symlinkFramework($$QMAKE_LIBDIR_QT, QtNetwork.framework/Versions/4/QtNetwork )
        QMAKE_POST_LINK += $$symlinkFramework($$QMAKE_LIBDIR_QT, QtSql.framework/Versions/4/QtSql )

        QMAKE_POST_LINK += $$installNameToolOnTarget(QxtCore)
        QMAKE_POST_LINK += $$installNameToolOnTarget(QxtNetwork)
        QMAKE_POST_LINK += $$installNameToolOnTarget(QxtWeb)
        QMAKE_POST_LINK += $$installNameToolOnTarget(QxtGui)
    }
    ######### Mac Debug End ##########

    ######### Mac Release ##########
    CONFIG(release, debug|release) {
        defineReplace( copyFramework ) {
            return( $$nc( mkdir -p $$FRAMEWORKSPATH/$$2 && rm -R $$FRAMEWORKSPATH/$$2 && cp -R -p $$1/$$2 $$FRAMEWORKSPATH/$$2 ) )
        }
        defineReplace( copyPlugin ) {
            return( $$nc( mkdir -p $$PLUGINSPATH/$$1 && cp -R -p  $$QMAKE_LIBDIR_QT/../plugins/$$1/$$2 $$PLUGINSPATH/$$1 ) )
        }
        defineReplace( installNameToolOnTarget  ) {
            return( $$nc( install_name_tool -change $${1}.framework/$${1} @executable_path/../Frameworks/$${1}.framework/$${1} $$TARGETEXECUTABLE ) )
        }
        defineReplace( installNameToolOnFramework  ) {
            return( $$nc( install_name_tool -change $${1}.framework/$${1} @executable_path/../Frameworks/$${1}.framework/$${1} $$FRAMEWORKSPATH/$${2}.framework/$${2} ) )
        }
        defineReplace( installNameToolQtOnTarget  ) {
            return( $$nc( install_name_tool -change $$QMAKE_LIBDIR_QT/$${1}.framework/Versions/4/$${1} @executable_path/../Frameworks/$${1}.framework/Versions/4/$${1} $$TARGETEXECUTABLE ) )
        }
        defineReplace( installNameToolQtOnQt  ) {
            return( $$nc( install_name_tool -change $$QMAKE_LIBDIR_QT/$${1}.framework/Versions/4/$${1} @executable_path/../Frameworks/$${1}.framework/Versions/4/$${1} $$FRAMEWORKSPATH/$${2}.framework/Versions/4/$${2} ) )
        }

        COPY_CONTENTS.target = copyContents
        COPY_CONTENTS.commands += $$nc( rm -Rf $$DESTDIR/$${TARGET}.app/Contents/Frameworks/ )
        COPY_CONTENTS.commands += $$nc( mkdir -p $$DESTDIR/$${TARGET}.app/Contents/Frameworks/ )
        COPY_CONTENTS.commands += $$copyFramework($$PWD/../lib/LBDatabase/lib, LBDatabase.framework )
        COPY_CONTENTS.commands += $$copyFramework($$PWD/../lib/LBGui/lib, LBGui.framework )
        COPY_CONTENTS.commands += $$copyFramework($$PWD/../frameworks, Sparkle.framework )
        COPY_CONTENTS.commands += $$copyFramework($$QXT_DIR/lib, QxtCore.framework )
        COPY_CONTENTS.commands += $$copyFramework($$QXT_DIR/lib, QxtWeb.framework )
        COPY_CONTENTS.commands += $$copyFramework($$QXT_DIR/lib, QxtGui.framework )
        COPY_CONTENTS.commands += $$copyFramework($$QXT_DIR/lib, QxtNetwork.framework )

        COPY_CONTENTS.commands += $$copyFramework($$QMAKE_LIBDIR_QT, QtCore.framework/Versions/4/QtCore )
        COPY_CONTENTS.commands += $$copyFramework($$QMAKE_LIBDIR_QT, QtGui.framework/Versions/4/QtGui )
        COPY_CONTENTS.commands += $$copyFramework($$QMAKE_LIBDIR_QT, QtNetwork.framework/Versions/4/QtNetwork )
        COPY_CONTENTS.commands += $$copyFramework($$QMAKE_LIBDIR_QT, QtSql.framework/Versions/4/QtSql )
        COPY_CONTENTS.commands += $$copyFramework($$QMAKE_LIBDIR_QT, QtGui.framework/Resources/qt_menu.nib/classes.nib )
        COPY_CONTENTS.commands += $$copyFramework($$QMAKE_LIBDIR_QT, QtGui.framework/Resources/qt_menu.nib/info.nib )
        COPY_CONTENTS.commands += $$copyFramework($$QMAKE_LIBDIR_QT, QtGui.framework/Resources/qt_menu.nib/keyedobjects.nib )

        COPY_CONTENTS.commands += $$copyPlugin(sqldrivers, libqsqlite.dylib)
        COPY_CONTENTS.commands += $$copyPlugin(imageformats, libqgif.dylib)
        COPY_CONTENTS.commands += $$copyPlugin(imageformats, libqjpeg.dylib)

        COPY_CONTENTS.commands += $$nc(cp $$PWD/../util/deployment/mac/qt.conf $$RESOURCESPATH)

        QMAKE_EXTRA_TARGETS += COPY_CONTENTS
        PRE_TARGETDEPS += copyContents

        QMAKE_POST_LINK += $$installNameToolOnTarget(LBDatabase)
        QMAKE_POST_LINK += $$installNameToolOnTarget(LBGui)
        QMAKE_POST_LINK += $$nc( install_name_tool -change @loader_path/../Frameworks/Sparkle.framework/Versions/A/Sparkle @executable_path/../Frameworks/Sparkle.framework/Versions/A/Sparkle $$TARGETEXECUTABLE )
        QMAKE_POST_LINK += $$installNameToolOnTarget(QxtCore)
        QMAKE_POST_LINK += $$installNameToolOnTarget(QxtNetwork)
        QMAKE_POST_LINK += $$installNameToolOnTarget(QxtWeb)
        QMAKE_POST_LINK += $$installNameToolOnTarget(QxtGui)

        QMAKE_POST_LINK += $$installNameToolQtOnTarget(QtCore)
        QMAKE_POST_LINK += $$installNameToolQtOnTarget(QtGui)
        QMAKE_POST_LINK += $$installNameToolQtOnTarget(QtNetwork)
        QMAKE_POST_LINK += $$installNameToolQtOnTarget(QtSql)

        QMAKE_POST_LINK += $$installNameToolQtOnQt(QtCore, QtSql)
        QMAKE_POST_LINK += $$installNameToolQtOnQt(QtCore, QtGui)
        QMAKE_POST_LINK += $$installNameToolQtOnQt(QtCore, QtNetwork)
        QMAKE_POST_LINK += $$installNameToolQtOnQt(QtNetwork, QtSql)
    }
    ######### End Mac Release ##########
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
    QMAKE_LFLAGS += -Wl,-enable-auto-import
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
    windows/livegame/adddrinkwidget.cpp \
    wizards/serverconnectdialog.cpp

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
    windows/livegame/adddrinkwidget.h \
    wizards/serverconnectdialog.h

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
    windows/livegame/adddrinkwidget.ui \
    wizards/serverconnectdialog.ui

OTHER_FILES += \
    resources/stylesheets/pointstable.css \
    resources/stylesheets/livegamesidebar.css

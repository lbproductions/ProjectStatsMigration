TARGET = LBGui
TEMPLATE = lib

contains(QT_VERSION, ^5) {
    QT += widgets
}

OBJECTS_DIR = $$OUT_PWD/../build/
DESTDIR = $$PWD/../lib/

COPY_HEADERS.target = copyHeaders
COPY_HEADERS.commands = cp -R $$PWD/*.h $$PWD/../include/$$TARGET
QMAKE_EXTRA_TARGETS += copyHeaders
PRE_TARGETDEPS += copyHeaders

macx {
    HEADERS += \
        mainwindow/sidebar/sidebaritemdelegatemac.h

    SOURCES += \
        mainwindow/sidebar/sidebaritemdelegatemac.cpp

    CONFIG += lib_bundle


    FRAMEWORK_HEADERS.version = Versions
    FRAMEWORK_HEADERS.files +=  \
        LBGui.h \
        mainwindow/mainwindow.h \
        mainwindow/sidebar/sidebar.h \
        mainwindow/sidebar/sidebarstatusbar.h \
        mainwindow/sidebar/sidebarstatusbardragbutton.h \
        mainwindow/sidebar/sidebartreeview.h \
        widgets/splitter.h \
        widgets/tabwidget.h \
        mainwindow/sidebar/sidebarparentcategorie.h \
        mainwindow/sidebar/sidebarchildcategorie.h \
        mainwindow/menubar.h \
        shared/actionsmanager.h \
        shared/action.h \
        shared/global.h \
        shared/recentfilesmanager.h \
        mainwindow/toolbar.h \
        widgets/groupbox.h \
        widgets/treeview.h \
        widgets/treeviewheader.h \
        widgets/listeditbuttonswidget.h \
        widgets/backgroundwidget.h \
        shared/autosavefile.h \
        preferenceswindow/preferenceswindow.h \
        preferenceswindow/preferencespage.h \
        widgets/sheet.h \
        mainwindow/view.h \
        widgets/itunesapplybar.h \
        widgets/label.h
    FRAMEWORK_HEADERS.path = Headers
    QMAKE_BUNDLE_DATA += FRAMEWORK_HEADERS

    CONFIG += qxt
    QXT     += widgets

    FRAMEWORKNAME = $${TARGET}.framework
    DYLIBNAME = $$FRAMEWORKNAME/$$TARGET
    DESTDYLIB = $$DESTDIR/$$DYLIBNAME
    FRAMEWORKSPATH = @executable_path/../Frameworks

    defineReplace( nc  ) {
        return( $$escape_expand(\\n\\t)$$1    )
    }

    ######### Mac Debug ##########

    CONFIG(debug, debug|release) {
        defineReplace( installNameTool  ) {
            return( $$nc( install_name_tool -change $$FRAMEWORKSPATH/$${2}.framework/$${2} $$1/$${2}.framework/$${2} $$DESTDYLIB ) )
        }

        QMAKE_POST_LINK += $$nc( install_name_tool -id $$FRAMEWORKSPATH/$$DYLIBNAME $$DESTDYLIB )
        QMAKE_POST_LINK += $$installNameTool($$QXT_DIR/lib, QxtCore)
        QMAKE_POST_LINK += $$installNameTool($$QXT_DIR/lib, QxtGui)
    }
    ######### Mac Debug End ##########

    ######### Mac Release ##########
    CONFIG(release, debug|release) {
        defineReplace( installNameTool  ) {
            return( $$nc( install_name_tool -change $${1}.framework/$${1} $$FRAMEWORKSPATH/$${1}.framework/$${1} $$DESTDYLIB ) )
        }
        defineReplace( installNameToolQtOnTarget  ) {
            return( $$nc( install_name_tool -change $$QMAKE_LIBDIR_QT/$${1}.framework/Versions/4/$${1} @executable_path/../Frameworks/$${1}.framework/Versions/4/$${1} $$DESTDYLIB ) )
        }

        QMAKE_POST_LINK += $$nc( install_name_tool -id $$FRAMEWORKSPATH/$$DYLIBNAME $$DESTDYLIB )
        QMAKE_POST_LINK += $$installNameTool(QxtCore)
        QMAKE_POST_LINK += $$installNameTool(QxtGui)
        QMAKE_POST_LINK += $$installNameToolQtOnTarget(QtGui)
        QMAKE_POST_LINK += $$installNameToolQtOnTarget(QtCore)
        QMAKE_POST_LINK += $$installNameToolQtOnTarget(QtSql)
    }
    ######### Mac End ##########
}

HEADERS += \
    LBGui.h \
    mainwindow/mainwindow.h \
    mainwindow/sidebar/sidebar.h \
    mainwindow/sidebar/sidebarstatusbar.h \
    mainwindow/sidebar/sidebarstatusbardragbutton.h \
    mainwindow/sidebar/sidebartreeview.h \
    widgets/splitter.h \
    widgets/tabwidget.h \
    mainwindow/sidebar/sidebarparentcategorie.h \
    mainwindow/sidebar/sidebarchildcategorie.h \
    mainwindow/menubar.h \
    shared/actionsmanager.h \
    shared/action.h \
    shared/global.h \
    shared/recentfilesmanager.h \
    mainwindow/toolbar.h \
    widgets/groupbox.h \
    widgets/treeview.h \
    widgets/treeviewheader.h \
    widgets/listeditbuttonswidget.h \
    widgets/backgroundwidget.h \
    shared/autosavefile.h \
    preferenceswindow/preferenceswindow.h \
    preferenceswindow/preferencespage.h \
    widgets/sheet.h \
    mainwindow/view.h \
    widgets/itunesapplybar.h \
    widgets/label.h

SOURCES += \
    mainwindow/mainwindow.cpp \
    mainwindow/sidebar/sidebar.cpp \
    mainwindow/sidebar/sidebarstatusbar.cpp \
    mainwindow/sidebar/sidebarstatusbardragbutton.cpp \
    mainwindow/sidebar/sidebartreeview.cpp \
    widgets/splitter.cpp \
    widgets/tabwidget.cpp \
    mainwindow/sidebar/sidebarparentcategorie.cpp \
    mainwindow/sidebar/sidebarchildcategorie.cpp \
    mainwindow/menubar.cpp \
    shared/actionsmanager.cpp \
    shared/action.cpp \
    shared/global.cpp \
    shared/recentfilesmanager.cpp \
    mainwindow/toolbar.cpp \
    widgets/groupbox.cpp \
    widgets/treeview.cpp \
    widgets/treeviewheader.cpp \
    widgets/listeditbuttonswidget.cpp \
    widgets/backgroundwidget.cpp \
    shared/autosavefile.cpp \
    preferenceswindow/preferenceswindow.cpp \
    preferenceswindow/preferencespage.cpp \
    widgets/sheet.cpp \
    mainwindow/view.cpp \
    widgets/itunesapplybar.cpp \
    widgets/label.cpp

OTHER_FILES += \
    ressources/sidebar/macos_lionmail/stylesheet.css \
    ressources/tabwidget/itunes_white/stylesheet.css \
    ressources/groupbox/itunes_white/stylesheet.css \
    ressources/pushbutton/itunes_white/stylesheet.css \
    ressources/listwidget/itunes_white/stylesheet.css \
    ressources/treeview/itunes_white/stylesheet.css \
    ressources/backgroundwidget/gray/stylesheet.css \
    ressources/sheet/stylesheet.css \
    ressources/itunesApplyBar/stylesheet.css \
    ressources/itunesApplyBar/stylesheet_button.css \
    ressources/toolbar/black/stylesheet.css \
    ressources/groupbox/iphoto_dark/stylesheet.css \
    ressources/scrollbar/iphoto_dark/stylesheet.css \
    ressources/pushbutton/iphotodarktab/stylesheet.css

RESOURCES += \
    ressources/sidebar/sidebar.qrc \
    ressources/tabwidget/tabwidget.qrc \
    ressources/groupbox/groupbox.qrc \
    ressources/pushbutton/pushbutton.qrc \
    ressources/listwidget/listwidget.qrc \
    ressources/treeview/treeview.qrc \
    ressources/backgroundwidget/backgroundwidget.qrc \
    ressources/preferenceswindow/preferenceswindow.qrc \
    ressources/sheet/sheet.qrc \
    ressources/itunesApplyBar/itunesApplyBar.qrc \
    ressources/toolbar/toolbar.qrc \
    ressources/scrollbar/scrollbar.qrc \
    ressources/general/general.qrc


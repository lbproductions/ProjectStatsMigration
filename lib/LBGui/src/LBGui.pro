TARGET = lbgui
TEMPLATE = lib

QT += sql widgets

OBJECTS_DIR = $$OUT_PWD/../build/
DESTDIR = $$OUT_PWD/../
INCLUDEPATH += $$PWD/include

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
    ressources/itunesApplyBar/stylesheet_button.css

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
    ressources/itunesApplyBar/itunesApplyBar.qrc

macx {
    HEADERS += \
        mainwindow/sidebar/sidebaritemdelegatemac.h

    SOURCES += \
        mainwindow/sidebar/sidebaritemdelegatemac.cpp
}

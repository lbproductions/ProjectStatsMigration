#ifndef LBGUI_H
#define LBGUI_H

#include <LBGui/mainwindow/mainwindow.h>
#include <LBGui/mainwindow/menubar.h>
#include <LBGui/mainwindow/toolbar.h>
#include <LBGui/mainwindow/view.h>
#include <LBGui/mainwindow/sidebar/sidebar.h>
#include <LBGui/mainwindow/sidebar/sidebarchildcategorie.h>
#include <LBGui/mainwindow/sidebar/sidebartreeview.h>
#include <LBGui/preferenceswindow/preferenceswindow.h>
#include <LBGui/preferenceswindow/preferencespage.h>
#include <LBGui/widgets/backgroundwidget.h>
#include <LBGui/widgets/tabwidget.h>
#include <LBGui/widgets/groupbox.h>
#include <LBGui/widgets/listeditbuttonswidget.h>
#include <LBGui/widgets/sheet.h>
#include <LBGui/widgets/splitter.h>
#include <LBGui/widgets/treeview.h>
#include <LBGui/shared/action.h>
#include <LBGui/shared/autosavefile.h>
#include <LBGui/shared/global.h>
#include <LBGui/shared/recentfilesmanager.h>


#define LBGUI_INIT_RESOURCES \
    Q_INIT_RESOURCE(tabwidget); \
    Q_INIT_RESOURCE(sidebar); \
    Q_INIT_RESOURCE(groupbox); \
    Q_INIT_RESOURCE(pushbutton); \
    Q_INIT_RESOURCE(listwidget); \
    Q_INIT_RESOURCE(backgroundwidget); \
    Q_INIT_RESOURCE(treeview); \
    Q_INIT_RESOURCE(preferenceswindow); \
    Q_INIT_RESOURCE(sheet)

#endif // LBGUI_H

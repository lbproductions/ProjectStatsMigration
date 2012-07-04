#ifndef LBGUI_H
#define LBGUI_H

#include "mainwindow/mainwindow.h"
#include "mainwindow/menubar.h"
#include "mainwindow/toolbar.h"
#include "mainwindow/view.h"
#include "mainwindow/sidebar/sidebar.h"
#include "mainwindow/sidebar/sidebarchildcategorie.h"
#include "mainwindow/sidebar/sidebartreeview.h"
#include "preferenceswindow/preferenceswindow.h"
#include "preferenceswindow/preferencespage.h"
#include "widgets/backgroundwidget.h"
#include "widgets/tabwidget.h"
#include "widgets/groupbox.h"
#include "widgets/listeditbuttonswidget.h"
#include "widgets/sheet.h"
#include "widgets/splitter.h"
#include "widgets/treeview.h"
#include "widgets/itunesapplybar.h"
#include "widgets/label.h"
#include "shared/action.h"
#include "shared/autosavefile.h"
#include "shared/global.h"
#include "shared/recentfilesmanager.h"


#define LBGUI_INIT_RESOURCES \
    Q_INIT_RESOURCE(general); \
    Q_INIT_RESOURCE(tabwidget); \
    Q_INIT_RESOURCE(sidebar); \
    Q_INIT_RESOURCE(groupbox); \
    Q_INIT_RESOURCE(pushbutton); \
    Q_INIT_RESOURCE(listwidget); \
    Q_INIT_RESOURCE(backgroundwidget); \
    Q_INIT_RESOURCE(treeview); \
    Q_INIT_RESOURCE(preferenceswindow); \
    Q_INIT_RESOURCE(sheet); \
    Q_INIT_RESOURCE(itunesApplyBar); \
    Q_INIT_RESOURCE(toolbar); \
    Q_INIT_RESOURCE(scrollbar)

#endif // LBGUI_H

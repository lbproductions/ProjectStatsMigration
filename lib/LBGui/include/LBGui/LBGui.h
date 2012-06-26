#ifndef LBGUI_H
#define LBGUI_H

#include "../../src/mainwindow/mainwindow.h"
#include "../../src/mainwindow/menubar.h"
#include "../../src/mainwindow/toolbar.h"
#include "../../src/mainwindow/view.h"
#include "../../src/mainwindow/sidebar/sidebar.h"
#include "../../src/mainwindow/sidebar/sidebarchildcategorie.h"
#include "../../src/mainwindow/sidebar/sidebartreeview.h"
#include "../../src/preferenceswindow/preferenceswindow.h"
#include "../../src/preferenceswindow/preferencespage.h"
#include "../../src/widgets/backgroundwidget.h"
#include "../../src/widgets/tabwidget.h"
#include "../../src/widgets/groupbox.h"
#include "../../src/widgets/listeditbuttonswidget.h"
#include "../../src/widgets/sheet.h"
#include "../../src/widgets/splitter.h"
#include "../../src/widgets/treeview.h"
#include "../../src/widgets/itunesapplybar.h"
#include "../../src/widgets/label.h"
#include "../../src/shared/action.h"
#include "../../src/shared/autosavefile.h"
#include "../../src/shared/global.h"
#include "../../src/shared/recentfilesmanager.h"


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

QT       += core gui sql

TARGET = LBDatabaseEditor
TEMPLATE = app

VERSION = 0.1
DEPLOY_DIR = $$OUT_PWD/../deploy
DESTDIR = $$OUT_PWD/../
OBJECTS_DIR = $$OUT_PWD/../build/
MYICON = $$PWD/resources/icon/ApplicationIcon.icns
APPCASTURL = http://dl.dropbox.com/u/140012/$$TARGET

DEFINES +=  'APPCASTURL=\'\"$$APPCASTURL\"\''

LBDATABASEDIR = $$PWD/../../../
LBGUIDIR = $$PWD/../../../../LBGui/
PROJECTSTATSOUTDIR = $$OUT_PWD/../../ProjectStats-build-desktop-Desktop_Qt_4_8_1_for_GCC__Qt_SDK__Debug
PROJECTSTATSDIR = $$PWD/../../../../../

INCLUDEPATH += $$LBDATABASEDIR/include
INCLUDEPATH += $$LBGUIDIR/include

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
    LIBS += -L$$PROJECTSTATSOUTDIR/lib/LBDatabase/
    LIBS += -llbdatabase

    LIBS += -L$$PROJECTSTATSOUTDIR/lib/LBGui/
    LIBS += -llbgui

    copyFrameworks.target = frameworks
    copyFrameworks.commands += rm -Rf $$DESTDIR/$${TARGET}.app/Contents/Frameworks/
    copyFrameworks.commands += $$snc( mkdir -p $$DESTDIR/$${TARGET}.app/Contents/Frameworks/ )
    copyFrameworks.commands += $$snc( cp -R $$PROJECTSTATSDIR/lib/LBDatabase/frameworks/* $$DESTDIR/$${TARGET}.app/Contents/Frameworks/ )
    copyFrameworks.commands += $$snc( cp -R $$PROJECTSTATSDIR/frameworks/* $$DESTDIR/$${TARGET}.app/Contents/Frameworks/ )
    copyFrameworks.commands += $$snc( cp -R $$QMAKE_LIBDIR_QT/QtCore.framework $$DESTDIR/$${TARGET}.app/Contents/Frameworks/ )
    copyFrameworks.commands += $$snc( cp -R $$QMAKE_LIBDIR_QT/QtNetwork.framework $$DESTDIR/$${TARGET}.app/Contents/Frameworks/ )

    copyDylibs.target = dylibs
    copyDylibs.commands += mkdir -p $$DESTDIR/$${TARGET}.app/Contents/MacOS/
    copyDylibs.commands += $$snc(   cp $$PROJECTSTATSOUTDIR/lib/LBDatabase/liblbdatabase.1.0.0.dylib $$DESTDIR/$${TARGET}.app/Contents/MacOS/ )
    copyDylibs.commands += $$snc(   cp $$PROJECTSTATSOUTDIR/lib/LBDatabase/liblbdatabase.1.dylib $$DESTDIR/$${TARGET}.app/Contents/MacOS/ )
    copyDylibs.commands += $$snc(   cp $$PROJECTSTATSOUTDIR/lib/LBGui/liblbgui.1.0.0.dylib $$DESTDIR/$${TARGET}.app/Contents/MacOS/ )
    copyDylibs.commands += $$snc(   cp $$PROJECTSTATSOUTDIR/lib/LBGui/liblbgui.1.dylib $$DESTDIR/$${TARGET}.app/Contents/MacOS/ )

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
    PRE_TARGETDEPS += dylibs frameworks

#     CONFIG(release, debug|release) {
#        QMAKE_POST_LINK += && rm -R $$DESTDIR/deploy && $$PWD/../util/deployment/mac/deploy.sh $$PWD $$OUT_PWD/../ $$DEPLOY_DIR $$MYICON $$TARGET $$APPCASTURL && \
#                             rm -R $$DESTDIR/deploy/Contents
#    }
}

SOURCES += main.cpp \
    mainwindow/mainwindow.cpp \
    mainwindow/actions.cpp \
    mainwindow/controller.cpp \
    mainwindow/sidebar.cpp \
    misc/logger.cpp \
    mainwindow/views/sampleview.cpp \
    preferences/updaterpreferences.cpp \
    mainwindow/views/entitytypeview.cpp \
    mainwindow/views/attributeeditor.cpp \
    mainwindow/views/functioneditor.cpp

HEADERS  += \
    mainwindow/mainwindow.h \
    mainwindow/actions.h \
    mainwindow/controller.h \
    mainwindow/sidebar.h \
    misc/logger.h \
    mainwindow/views/sampleview.h \
    misc/updater.h \
    preferences/updaterpreferences.h \
    mainwindow/views/entitytypeview.h \
    mainwindow/views/attributeeditor.h \
    mainwindow/views/functioneditor.h

OTHER_FILES += \
    ../util/deployment/mac/deploy.sh

FORMS += \
    mainwindow/views/entitytypeview.ui \
    mainwindow/views/attributeeditor.ui \
    mainwindow/views/functioneditor.ui














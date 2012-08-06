QT       += core gui sql

TARGET = LBDatabaseEditor
TEMPLATE = app

VERSION = 0.1
DEPLOY_DIR = $$OUT_PWD/../deploy
DESTDIR = $$OUT_PWD/../
OBJECTS_DIR = $$OUT_PWD/../build/
MYICON = $$PWD/resources/icons/AppIcon.icns
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

QT += network

macx {
    LIBS += \
        -F$$LBDATABASEDIR/lib/ \
        -F$$LBGUIDIR/lib/ \
        -framework AppKit \
        -framework LBGui \
        -framework LBDatabase

    APPCONTENTSPATH = $$DESTDIR/$${TARGET}.app/Contents
    PLUGINSPATH = $$APPCONTENTSPATH/PlugIns
    FRAMEWORKSPATH = $$APPCONTENTSPATH/Frameworks
    TARGETEXECUTABLE = $$APPCONTENTSPATH/MacOS/$$TARGET
    RESOURCESPATH = $$APPCONTENTSPATH/Resources

    QXT_DIR = $$PWD/../../../../../lib/libqxt

    CONFIG += qxt

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

        QMAKE_POST_LINK += $$symlinkFramework($$LBDATABASEDIR/lib, LBDatabase.framework/LBDatabase)
        QMAKE_POST_LINK += $$symlinkFramework($$LBGUIDIR/lib, LBGui.framework/LBGui)
        QMAKE_POST_LINK += $$nc( install_name_tool -change @loader_path/../Frameworks/Sparkle.framework/Versions/A/Sparkle $$PWD/../frameworks/Sparkle.framework/Sparkle $$TARGETEXECUTABLE )
        QMAKE_POST_LINK += $$symlinkFramework($$QXT_DIR/lib, QxtCore.framework/QxtCore)
        QMAKE_POST_LINK += $$symlinkFramework($$QXT_DIR/lib, QxtNetwork.framework/QxtNetwork)
        QMAKE_POST_LINK += $$symlinkFramework($$QXT_DIR/lib, QxtWeb.framework/QxtWeb)
        QMAKE_POST_LINK += $$symlinkFramework($$QXT_DIR/lib, QxtWidgets.framework/QxtWidgets)

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

SOURCES += main.cpp \
    mainwindow/mainwindow.cpp \
    mainwindow/actions.cpp \
    mainwindow/controller.cpp \
    mainwindow/sidebar.cpp \
    misc/logger.cpp \
    mainwindow/views/sampleview.cpp \
    preferences/updaterpreferences.cpp \
    mainwindow/views/attributeeditor.cpp \
    mainwindow/views/functioneditor.cpp \
    mainwindow/views/relationseditor.cpp \
    graphvizexporter.cpp \
    entitytypewriter.cpp \
    cppexporter.cpp \
    contextwriter.cpp \
    calculatorwriter.cpp \
    writer.cpp \
    storagewriter.cpp \
    mainwindow/views/propertiesview.cpp \
    mainwindow/views/entitytypeview.cpp \
    mainwindow/views/dependenciesview.cpp \
    mainwindow/views/dependencyeditor.cpp

HEADERS  += \
    mainwindow/mainwindow.h \
    mainwindow/actions.h \
    mainwindow/controller.h \
    mainwindow/sidebar.h \
    misc/logger.h \
    mainwindow/views/sampleview.h \
    misc/updater.h \
    preferences/updaterpreferences.h \
    mainwindow/views/attributeeditor.h \
    mainwindow/views/functioneditor.h \
    mainwindow/views/relationseditor.h \
    graphvizexporter.h \
    entitytypewriter.h \
    cppexporter.h \
    contextwriter.h \
    calculatorwriter.h \
    writer.h \
    storagewriter.h \
    mainwindow/views/propertiesview.h \
    mainwindow/views/entitytypeview.h \
    mainwindow/views/dependenciesview.h \
    mainwindow/views/dependencyeditor.h

OTHER_FILES += \
    ../util/deployment/mac/deploy.sh

FORMS += \
    mainwindow/views/attributeeditor.ui \
    mainwindow/views/functioneditor.ui \
    mainwindow/views/relationseditor.ui \
    mainwindow/views/propertiesview.ui \
    mainwindow/views/dependenciesview.ui \
    mainwindow/views/dependencyeditor.ui

RESOURCES += \
    resources/icons/icons.qrc














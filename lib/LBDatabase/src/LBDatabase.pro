TARGET = LBDatabase
TEMPLATE = lib
VERSION = 0.0

QT += sql network

DEFINES *= QT_USE_QSTRINGBUILDER

OBJECTS_DIR = $$OUT_PWD/../build/
DESTDIR = $$PWD/../lib/

CONFIG += qxt
QXT     += web

macx {
    CONFIG += lib_bundle

    FRAMEWORK_HEADERS.version = Versions
    FRAMEWORK_HEADERS.files +=  \
            LBDatabase.h \
            local/column.h \
            local/database.h \
            local/row.h \
            local/table.h \
            entity.h \
            storage.h \
            context.h \
            entitytype.h \
            attribute.h \
            attributevalue.h \
            relation.h \
            property.h \
            propertyvalue.h \
            relationvalue.h \
            relationvalue.cpp \
            relationvaluebase.h \
            function.h \
            functionvalue.h \
            calculator.h \
            enumattribute.h \
            storagedriver.h \
            local/localstoragedriver.h \
            server/restserver.h

    FRAMEWORK_HEADERS.path = Headers
    QMAKE_BUNDLE_DATA += FRAMEWORK_HEADERS

    FRAMEWORKNAME = $${TARGET}.framework
    DYLIBNAME = $$FRAMEWORKNAME/$$TARGET
    DESTDYLIB = $$DESTDIR/$$DYLIBNAME
    FRAMEWORKSPATH = @executable_path/../Frameworks

    defineReplace( nc  ) {
        return( $$escape_expand(\\n\\t)$$1    )
    }
    defineReplace( installNameTool  ) {
        return( $$nc( install_name_tool -change $${1}.framework/Versions/0/$${1} $$FRAMEWORKSPATH/$${1}.framework/$${1} $$DESTDYLIB ) )
    }
    defineReplace( installNameToolQtOnTarget  ) {
        return( $$nc( install_name_tool -change $$QMAKE_LIBDIR_QT/$${1}.framework/Versions/4/$${1} @executable_path/../Frameworks/$${1}.framework/Versions/4/$${1} $$DESTDYLIB ) )
    }

    QMAKE_POST_LINK += install_name_tool -id $$FRAMEWORKSPATH/$$DYLIBNAME $$DESTDYLIB
    QMAKE_POST_LINK += $$installNameTool(QxtCore)
    QMAKE_POST_LINK += $$installNameTool(QxtWeb)
    QMAKE_POST_LINK += $$installNameTool(QxtNetwork)
    QMAKE_POST_LINK += $$installNameToolQtOnTarget(QtNetwork)
    QMAKE_POST_LINK += $$installNameToolQtOnTarget(QtCore)
    QMAKE_POST_LINK += $$installNameToolQtOnTarget(QtSql)

#install_name_tool -id @executable_path/../Frameworks/QxtCore.framework/QxtCore QxtCore.framework/QxtCore
#install_name_tool -id @executable_path/../Frameworks/QxtNetwork.framework/QxtNetwork QxtNetwork.framework/QxtNetwork
#install_name_tool -id @executable_path/../Frameworks/QxtWeb.framework/QxtWeb QxtWeb.framework/QxtWeb
#install_name_tool -id @executable_path/../Frameworks/QxtGui.framework/QxtGui QxtGui.framework/QxtGui

#install_name_tool -change QxtCore.framework/Versions/0/QxtCore @executable_path/../Frameworks/QxtCore.framework/QxtCore QxtNetwork.framework/QxtNetwork
#install_name_tool -change QxtCore.framework/Versions/0/QxtCore @executable_path/../Frameworks/QxtCore.framework/QxtCore QxtGui.framework/QxtGui
#install_name_tool -change QxtCore.framework/Versions/0/QxtCore @executable_path/../Frameworks/QxtCore.framework/QxtCore QxtWeb.framework/QxtWeb
#install_name_tool -change QxtNetwork.framework/Versions/0/QxtNetwork @executable_path/../Frameworks/QxtNetwork.framework/QxtNetwork QxtWeb.framework/QxtWeb

#install_name_tool -change /Users/niklas/QtSDK/Desktop/Qt/4.8.1/gcc/lib/QtCore.framework/Versions/4/QtCore @executable_path/../Frameworks/QtCore.framework/Versions/4/QtCore QxtCore.framework/QxtCore
#install_name_tool -change /Users/niklas/QtSDK/Desktop/Qt/4.8.1/gcc/lib/QtCore.framework/Versions/4/QtCore @executable_path/../Frameworks/QtCore.framework/Versions/4/QtCore QxtNetwork.framework/QxtNetwork
#install_name_tool -change /Users/niklas/QtSDK/Desktop/Qt/4.8.1/gcc/lib/QtCore.framework/Versions/4/QtCore @executable_path/../Frameworks/QtCore.framework/Versions/4/QtCore QxtGui.framework/QxtGui
#install_name_tool -change /Users/niklas/QtSDK/Desktop/Qt/4.8.1/gcc/lib/QtCore.framework/Versions/4/QtCore @executable_path/../Frameworks/QtCore.framework/Versions/4/QtCore QxtWeb.framework/QxtWeb

#install_name_tool -change /Users/niklas/QtSDK/Desktop/Qt/4.8.1/gcc/lib/QtNetwork.framework/Versions/4/QtNetwork @executable_path/../Frameworks/QtNetwork.framework/Versions/4/QtNetwork QxtNetwork.framework/QxtNetwork
#install_name_tool -change /Users/niklas/QtSDK/Desktop/Qt/4.8.1/gcc/lib/QtNetwork.framework/Versions/4/QtNetwork @executable_path/../Frameworks/QtNetwork.framework/Versions/4/QtNetwork QxtWeb.framework/QxtWeb

#install_name_tool -change /Users/niklas/QtSDK/Desktop/Qt/4.8.1/gcc/lib/QtGui.framework/Versions/4/QtGui @executable_path/../Frameworks/QtGui.framework/Versions/4/QtGui QxtGui.framework/QxtGui
}

HEADERS += \
    LBDatabase.h \
    local/column.h \
    local/database.h \
    local/row.h \
    local/table.h \
    entity.h \
    storage.h \
    context.h \
    entitytype.h \
    attribute.h \
    attributevalue.h \
    relation.h \
    property.h \
    propertyvalue.h \
    relationvalue.h \
    function.h \
    functionvalue.h \
    calculator.h \
    enumattribute.h \
    attribute_p.h \
    storagedriver.h \
    local/localstoragedriver.h \
    relationvaluebase.h \
    relationvaluebase_p.h \
    server/restserver.h \
    server/contentsservice.h \
<<<<<<< HEAD
    restdriver/reststoragedriver.h
=======
    restdriver/reststoragedriver.h \
    server/jsonexporter.h
>>>>>>> refs/heads/uncommited

SOURCES += \
    local/column.cpp \
    local/database.cpp \
    local/row.cpp \
    local/table.cpp \
    entity.cpp \
    storage.cpp \
    context.cpp \
    entitytype.cpp \
    attribute.cpp \
    attributevalue.cpp \
    relation.cpp \
    property.cpp \
    propertyvalue.cpp \
    function.cpp \
    functionvalue.cpp \
    calculator.cpp \
    enumattribute.cpp \
    storagedriver.cpp \
    local/localstoragedriver.cpp \
    relationvaluebase.cpp \
    relationvalue.cpp \
    server/restserver.cpp \
    server/contentsservice.cpp \
<<<<<<< HEAD
    restdriver/reststoragedriver.cpp
=======
    restdriver/reststoragedriver.cpp \
    server/jsonexporter.cpp
>>>>>>> refs/heads/uncommited

TARGET = lbdatabase
TEMPLATE = lib

QT += sql network
DEFINES *= QT_USE_QSTRINGBUILDER

OBJECTS_DIR = $$OUT_PWD/../build/
DESTDIR = $$OUT_PWD/../

INCLUDEPATH += $$PWD/include

macx {
    QMAKE_LFLAGS += -F$$PWD/../frameworks/

    CONFIG += qxt
    QXT     += core web network
    QXT_DIR = $${PWD}/../lib/libqxt-0.6.2
    LIBS += -F$${QXT_DIR}/lib \
        -framework QxtCore \
        -framework QxtNetwork \
        -framework QxtWeb
    INCLUDEPATH += $${QXT_DIR}/include
    INCLUDEPATH += $${QXT_DIR}/src/core
    INCLUDEPATH += $${QXT_DIR}/src/web
    INCLUDEPATH += $${QXT_DIR}/src/network
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
    relationvalue_p.h \
    function.h \
    functionvalue.h \
    calculator.h \
    export/graphvizexporter.h \
    export/cppexporter.h \
    export/storagewriter.h \
    export/writer.h \
    export/contextwriter.h \
    export/entitytypewriter.h \
    export/calculatorwriter.h \
    enumattribute.h \
    attribute_p.h \
    server/restserver.h \
    storagedriver.h \
    local/localstoragedriver.h

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
    relationvalue.cpp \
    function.cpp \
    functionvalue.cpp \
    calculator.cpp \
    export/graphvizexporter.cpp \
    export/cppexporter.cpp \
    export/storagewriter.cpp \
    export/writer.cpp \
    export/contextwriter.cpp \
    export/entitytypewriter.cpp \
    export/calculatorwriter.cpp \
    enumattribute.cpp \
    server/restserver.cpp \
    storagedriver.cpp \
    local/localstoragedriver.cpp

OTHER_FILES +=


TARGET = lbdatabase
TEMPLATE = lib

QT += sql network
DEFINES *= QT_USE_QSTRINGBUILDER

OBJECTS_DIR = $$OUT_PWD/../build/
DESTDIR = $$OUT_PWD/../

INCLUDEPATH += $$PWD/include

macx {
    QMAKE_LFLAGS += -F$$PWD/../frameworks/
    LIBS += -framework QxtCore \
            -framework QxtNetwork \
            -framework QxtWeb

    INCLUDEPATH += $$PWD/../include/QxtCore \
                    $$PWD/../include/QxtWeb \
                    $$PWD/../include/QxtNetwork \
                    $$PWD/../frameworks/QxtCore.framework/Headers \
                    $$PWD/../frameworks/QxtWeb.framework/Headers \
                    $$PWD/../frameworks/QxtNetwork.framework/Headers
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
    concreterelation.h \
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


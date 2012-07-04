TEMPLATE = lib

QXT_DIR = $$PWD/libqxt

!exists($$QXT_DIR/lib/QxtCore.framework) {
    QMAKEBIN = $$QMAKE_LIBDIR_QT/../bin/qmake

    defineReplace( nc  ) {
        return( $$escape_expand(\\n\\t)$$1    )
    }
    defineReplace( installNameToolOnFramework  ) {
        return( $$nc( install_name_tool -change $${1}.framework/Versions/0/$${1} @executable_path/../Frameworks/$${1}.framework/$${1} $$QXT_DIR/lib/$${2}.framework/Versions/0/$${2} ) )
    }

    MAKE_QXT.target = makeQxt
    MAKE_QXT.commands += $$nc( $$QXT_DIR/configure \
        -qmake-bin $$QMAKEBIN \
        -prefix $$QXT_DIR/deploy \
        -libdir $$QXT_DIR/lib )
    #    -featuredir $$QXT_DIR/deploy/features )
    MAKE_QXT.commands += $$nc( make $$QXT_DIR )
    MAKE_QXT.commands += $$nc( make $$QXT_DIR install )
    MAKE_QXT.commands += $$installNameToolOnFramework( QxtCore, QxtWeb )
    MAKE_QXT.commands += $$installNameToolOnFramework( QxtCore, QxtNetwork )
    MAKE_QXT.commands += $$installNameToolOnFramework( QxtCore, QxtWidgets )
    MAKE_QXT.commands += $$installNameToolOnFramework( QxtNetwork, QxtWeb )

    PRE_TARGETDEPS += makeQxt
    QMAKE_EXTRA_TARGETS += MAKE_QXT




}

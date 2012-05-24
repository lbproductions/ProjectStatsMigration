TEMPLATE = subdirs

SUBDIRS += \
    lib/LBDatabase/lib/libqxt-0.6.2/libqxt.pro \
    lib/LBDatabase/src/LBDatabase.pro \
    lib/LBGui/src/LBGui.pro \
    src/src.pro

CONFIG += ordered

OTHER_FILES += README.md  \
    util/deployment/mac/deploy.sh

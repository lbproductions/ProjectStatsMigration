TEMPLATE = subdirs

SUBDIRS += \
    lib/libs.pro \
    lib/libqxt \
    lib/LBDatabase/src/LBDatabase.pro \
    lib/LBGui/src/LBGui.pro \
    src/src.pro

CONFIG += ordered

OTHER_FILES += README.md  \
    util/deployment/mac/deploy.sh  \
    util/deployment/win/deploy.bat

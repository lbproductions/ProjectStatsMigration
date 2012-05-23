#include "global.h"

#include <QSettings>
#include <QFileDialog>
#include <QDesktopServices>

namespace LBGui {

QString getOpenFileName(const QString &windowTitle, const QString &fileDesc)
{
    QSettings settings;
    QString lastOpenFolder = settings.value("lastOpenFolder",
                                            QDesktopServices::storageLocation(QDesktopServices::HomeLocation)).toString();
    QString fileName = QFileDialog::getOpenFileName(0,windowTitle, lastOpenFolder, fileDesc);

    QFile file(fileName);

    if(file.exists() || file.open(QIODevice::WriteOnly)) {
        settings.setValue("lastOpenFolder",QFileInfo(file).absolutePath());
        return file.fileName();
    }

    return QString();
}

QString getSaveFileName(const QString &windowTitle, const QString &fileDesc)
{
    QSettings settings;
    QString lastOpenFolder = settings.value("lastOpenFolder",
                                            QDesktopServices::storageLocation(QDesktopServices::HomeLocation)).toString();
    return QFileDialog::getSaveFileName(0,windowTitle, lastOpenFolder, fileDesc);
}

QString getSaveDirName(const QString &windowTitle)
{
    QSettings settings;
    QString lastOpenFolder = settings.value("lastOpenFolder",
                                            QDesktopServices::storageLocation(QDesktopServices::HomeLocation)).toString();
    return QFileDialog::getExistingDirectory(0,windowTitle, lastOpenFolder, QFileDialog::ShowDirsOnly
                                             | QFileDialog::DontResolveSymlinks);
}

} // namespace LBGui

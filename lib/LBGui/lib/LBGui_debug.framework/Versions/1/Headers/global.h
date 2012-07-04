#ifndef LBGUI_HELPER_H
#define LBGUI_HELPER_H

#include <QObject>

namespace LBGui {

QString getOpenFileName(const QString &windowTitle, const QString &fileDesc);
QString getSaveFileName(const QString &windowTitle, const QString &fileDesc);
QString getSaveDirName(const QString &windowTitle);

} // namespace LBGui

#endif // LBGUI_HELPER_H

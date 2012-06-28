#ifndef LBGUI_AUTOSAVEFILE_H
#define LBGUI_AUTOSAVEFILE_H

#include <QObject>

#include <QFile>
#include <QHash>

namespace LBGui {

class AutosaveFile : public QObject
{
    Q_OBJECT
public:
    static AutosaveFile *instance(const QString &fileName);
    ~AutosaveFile();

    void save();
    
    QString copyFileName();

private:
    explicit AutosaveFile(const QString &name, QObject *parent = 0);

    static QHash<QString, AutosaveFile*> instances;

    QFile m_original;
    QFile m_copy;
};

} // namespace LBGui

#endif // LBGUI_AUTOSAVEFILE_H

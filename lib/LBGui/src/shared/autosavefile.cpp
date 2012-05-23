#include "autosavefile.h"

#include <QDebug>
#include <QMutex>

namespace LBGui {

QHash<QString, AutosaveFile*> AutosaveFile::instances = QHash<QString, AutosaveFile*>();

AutosaveFile *AutosaveFile::instance(const QString &fileName)
{
    static QMutex mutex(QMutex::Recursive);
    static QObject guard;
    QMutexLocker locker(&mutex);
    Q_UNUSED(locker)

    if(AutosaveFile::instances.contains(fileName)) {
        return AutosaveFile::instances.value(fileName);
    }

    AutosaveFile* autosaveFile = new AutosaveFile(fileName, &guard);
    AutosaveFile::instances.insert(fileName, autosaveFile);
    return autosaveFile;
}

AutosaveFile::AutosaveFile(const QString &name, QObject *parent) :
    QObject(parent),
    m_original(name),
    m_copy(name+QLatin1String(".lbautosave"))
{
    m_copy.remove();
    m_original.copy(m_copy.fileName());
}

AutosaveFile::~AutosaveFile()
{
    m_copy.remove();
}

void AutosaveFile::save()
{
    m_original.remove();
    m_copy.copy(m_original.fileName());
}

QString AutosaveFile::copyFileName()
{
    return m_copy.fileName();
}

} // namespace LBGui

#include "recentfilesmanager.h"

#include <QAction>
#include <QMenu>
#include <QSettings>

namespace LBGui {

RecentFilesManager::RecentFilesManager(QObject *parent) :
    QObject(parent),
    m_actions(QHash<QString, QAction*>()),
    m_files(QStringList()),
    m_maxFiles(5),
    m_menu(new QMenu(tr("O&pen recent"))),
    m_settingsName("RecentFiles")
{
    m_menu->addAction(RecentFilesManager::noEntries());
}

QString RecentFilesManager::settingsName() const
{
    return m_settingsName;
}

void RecentFilesManager::setSettingsName(const QString &settingsName)
{
    m_settingsName = settingsName;
}

QMenu *RecentFilesManager::recentFilesMenu()
{
    return m_menu;
}

int RecentFilesManager::maxFiles() const
{
    return m_maxFiles;
}

QStringList RecentFilesManager::files() const
{
    return m_files;
}

void RecentFilesManager::addFile(const QString &fileName)
{
    removeFile(fileName);
    QAction *before = 0;
    if(!m_files.isEmpty()) {
        before = m_actions.value(m_files.first());
    }
    m_files.prepend(fileName);

    if(m_files.size() == 1) {
        m_menu->clear();
    }

    QAction *action = constructAction(fileName);
    m_actions.insert(fileName, action);
    m_menu->insertAction(before, action);

    if(m_files.size() == 1) {
        m_menu->addSeparator();
        m_menu->addAction(RecentFilesManager::clearAction());
    }


    emit fileAdded(fileName);
    emit changed();

    if(m_files.size() > m_maxFiles) {
        removeLast();
    }

    QSettings settings;
    settings.setValue(m_settingsName, m_files);
}

void RecentFilesManager::populateFromSettings()
{
    QSettings settings;
    foreach(QString fileName, settings.value(m_settingsName).toStringList()) {
        addFile(fileName);
    }
}

void RecentFilesManager::setMaxFiles(int maxFiles)
{
    m_maxFiles = maxFiles;
    while(m_files.size() > m_maxFiles) {
        removeLast();
    }
}

void RecentFilesManager::removeFile(const QString &fileName)
{
    QString file = fileName;
    if(file.isNull()) {
        file = m_files.takeLast();
    }
    else {
        m_files.removeAll(file);
    }

    QAction *action = m_actions.take(fileName);
    m_menu->removeAction(action);
//    action->deleteLater();

    QSettings settings;
    settings.setValue(m_settingsName, m_files);

    emit fileRemoved(fileName);
    emit changed();
}

void RecentFilesManager::removeLast()
{
    removeFile();
}

QAction *RecentFilesManager::constructAction(const QString &fileName)
{
    QAction *action = new QAction(fileName, this);
    action->setData(fileName);
    connect(action, SIGNAL(triggered()), this, SLOT(on_actionTriggered()));
    return action;
}

QAction *RecentFilesManager::noEntries()
{
    static QAction action(tr("No entries"), 0);
    action.setEnabled(false);
    return &action;
}

QAction *RecentFilesManager::clearAction()
{
    static QAction action(tr("&Clear menu"),0);
    connect(&action, SIGNAL(triggered()), this, SLOT(clear()));
    return &action;
}

void RecentFilesManager::on_actionTriggered()
{
    QAction *action = static_cast<QAction*>(sender());
    emit fileTriggered(action->data().toString());
}

void RecentFilesManager::clear()
{
    while(!m_files.isEmpty()) {
        removeLast();
    }
    m_menu->clear();
    m_menu->addAction(RecentFilesManager::noEntries());
}


} // namespace LBGui

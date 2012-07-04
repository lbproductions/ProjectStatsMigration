#ifndef LBGUI_RECENTFILESMANAGER_H
#define LBGUI_RECENTFILESMANAGER_H

#include <QObject>

#include <QStringList>
#include <QHash>

class QMenu;
class QAction;

namespace LBGui {

class RecentFilesManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int maxFiles READ maxFiles WRITE setMaxFiles)
    Q_PROPERTY(QString  settingsName READ settingsName WRITE setSettingsName)

public:
    explicit RecentFilesManager(QObject *parent = 0);

    int maxFiles() const;
    void setMaxFiles(int maxFiles);

    void addFile(const QString &fileName);

    void populateFromSettings();

    QStringList files() const;

    QMenu *recentFilesMenu();

    QString    settingsName () const;
    void    setSettingsName (const QString &settingsName);

signals:
    void fileTriggered(QString);
    void fileAdded(QString);
    void fileRemoved(QString);
    void changed();

private slots:
    void on_actionTriggered();
    void clear();

private:
    void removeFile(const QString &fileName = QString());
    void removeLast();

    QAction *constructAction(const QString &fileName);

    static QAction *noEntries();
    QAction *clearAction();

    QHash<QString, QAction*> m_actions;
    QStringList m_files;
    int m_maxFiles;
    QMenu *m_menu;
    QString m_settingsName;
};

} // namespace LBGui

#endif // LBGUI_RECENTFILESMANAGER_H

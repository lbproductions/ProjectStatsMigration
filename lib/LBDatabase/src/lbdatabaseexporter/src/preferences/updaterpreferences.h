#ifndef UPDATERPREFERENCES_H
#define UPDATERPREFERENCES_H

#include <LBGui/LBGui.h>

#include "../misc/updater.h"

class UpdaterPreferences : public LBGui::PreferencesPage
{
    Q_OBJECT
public:
    explicit UpdaterPreferences(Updater *updater, LBGui::PreferencesWindow *parent);

    static void initializeUpdater(Updater *updater);

signals:
    void checkForUpdatesRequested();
    void automaticChecksToggled(bool);
    void automaticDownloadsToggled(bool);

private Q_SLOTS:
    void toggleAutomaticChecks(bool);
    void toggleAutomaticDownloads(bool);
    
private:
    Updater *updater;
};

#endif // UPDATERPREFERENCES_H

#ifndef WINSPARKLEUPDATER_H
#define WINSPARKLEUPDATER_H

#include "Updater.h"

#include <QString>

class WinSparkleUpdater : public Updater
{
    public:
        WinSparkleUpdater(const QString& url);
        ~WinSparkleUpdater();

        void checkForUpdates();
        void checkForUpdatesInBackground();

        void setAutomaticallyChecksForUpdates(bool check);
        void setAutomaticallyDownloadsUpdates(bool download);
};

#endif // WINSPARKLEUPDATER_H

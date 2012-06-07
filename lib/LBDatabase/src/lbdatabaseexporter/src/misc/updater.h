#ifndef UPDATER_H
#define UPDATER_H

class Updater
{
public:
    virtual void checkForUpdates() = 0;
    virtual void checkForUpdatesInBackground() = 0;

    virtual void setAutomaticallyChecksForUpdates(bool check) = 0;
    virtual void setAutomaticallyDownloadsUpdates(bool download) = 0;
};

#endif // UPDATER_H

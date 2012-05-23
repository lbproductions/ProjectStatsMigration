#ifndef SPARKLEUPDATER_H
#define SPARKLEUPDATER_H

#include "Updater.h"

#include <QString>

class SparkleUpdater : public Updater
{
    public:
	SparkleUpdater(const QString& url);
	~SparkleUpdater();

	virtual void checkForUpdates();
	virtual void checkForUpdatesInBackground();

    void setAutomaticallyChecksForUpdates(bool check);
    void setAutomaticallyDownloadsUpdates(bool download);

    private:
	class Private;
	Private* d;
};

#endif // SPARKLEUPDATER_H

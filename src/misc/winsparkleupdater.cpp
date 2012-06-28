#include "winsparkleupdater.h"

#include "../frameworks/WinSparkle-0.3/winsparkle.h"

WinSparkleUpdater::WinSparkleUpdater(const QString &url)
{
    win_sparkle_set_appcast_url(url.toAscii());
}

WinSparkleUpdater::~WinSparkleUpdater()
{
    win_sparkle_cleanup();
}

void WinSparkleUpdater::checkForUpdates()
{
    win_sparkle_init();
    win_sparkle_check_update_with_ui();
}
void WinSparkleUpdater::checkForUpdatesInBackground()
{
    win_sparkle_init();
}

void WinSparkleUpdater::setAutomaticallyChecksForUpdates(bool check)
{
}

void WinSparkleUpdater::setAutomaticallyDownloadsUpdates(bool download)
{
}

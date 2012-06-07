#include "updaterpreferences.h"

#include <QCheckBox>
#include <QFormLayout>
#include <QPushButton>
#include <QSettings>

namespace {
const QString AutomaticChecksSetting("updater/checkAutomatically");
const QString AutomaticalDownloadsUpdatesSetting("updater/automaticdownloads");
}

UpdaterPreferences::UpdaterPreferences(Updater *updater, LBGui::PreferencesWindow *parent) :
    LBGui::PreferencesPage(parent),
    updater(updater)
{
    setName(tr("Updates"));
    setIcon(QIcon(":/preferenceswindow/mac/apple-update"));

    QSettings settings;
    QFormLayout *layout = new QFormLayout(this);

    QCheckBox *checkAutomaticallyCheckBox = new QCheckBox(this);
    bool checkAutomatically = settings.value(AutomaticChecksSetting, QVariant(true)).toBool();
    checkAutomaticallyCheckBox->setText(tr("Check for updates automatically"));
    checkAutomaticallyCheckBox->setChecked(checkAutomatically);
    connect(checkAutomaticallyCheckBox, SIGNAL(toggled(bool)), this, SLOT(toggleAutomaticChecks(bool)));
    connect(checkAutomaticallyCheckBox, SIGNAL(toggled(bool)), this, SIGNAL(automaticChecksToggled(bool)));
    layout->addRow(tr("Updates:"), checkAutomaticallyCheckBox);

    QCheckBox *automaticallyDownloadCheckBox = new QCheckBox(this);
    bool downloadAutomatically= settings.value(AutomaticalDownloadsUpdatesSetting, QVariant(true)).toBool();
    automaticallyDownloadCheckBox->setText(tr("Download updates automatically"));
    automaticallyDownloadCheckBox->setChecked(downloadAutomatically);
    connect(automaticallyDownloadCheckBox, SIGNAL(toggled(bool)), this, SLOT(toggleAutomaticDownloads(bool)));
    connect(automaticallyDownloadCheckBox, SIGNAL(toggled(bool)), this, SIGNAL(automaticDownloadsToggled(bool)));
    layout->addRow(tr(""), automaticallyDownloadCheckBox);

    QPushButton *checkNowButton = new QPushButton(this);
    checkNowButton->setText(tr("Check now"));
    connect(checkNowButton, SIGNAL(clicked()), this, SIGNAL(checkForUpdatesRequested()));
    layout->addRow(tr(""), checkNowButton);

    setLayout(layout);
}

void UpdaterPreferences::initializeUpdater(Updater *updater)
{
    QSettings settings;
    bool checksForUpdates = settings.value(AutomaticChecksSetting, QVariant(true)).toBool();
    bool automaticdownloads = settings.value(AutomaticalDownloadsUpdatesSetting, QVariant(false)).toBool();

    updater->setAutomaticallyChecksForUpdates(checksForUpdates);
    updater->setAutomaticallyDownloadsUpdates(automaticdownloads);

    if(checksForUpdates)
        updater->checkForUpdatesInBackground();
}

void UpdaterPreferences::toggleAutomaticChecks(bool check)
{
    QSettings settings;
    settings.setValue(AutomaticChecksSetting, QVariant(check));

    updater->setAutomaticallyChecksForUpdates(check);
}

void UpdaterPreferences::toggleAutomaticDownloads(bool download)
{
    QSettings settings;
    settings.setValue(AutomaticalDownloadsUpdatesSetting, QVariant(download));

    updater->setAutomaticallyDownloadsUpdates(download);
}

#ifndef NEWGAMEWIZARD_H
#define NEWGAMEWIZARD_H

#include <QWizard>

class PlacesComboBox;
class Storage;

namespace Wizards
{

namespace NewGame {
    class LiveGameGeneralOptionsWidget;
    class LiveDokoGameOptionsWidget;
}

/**
 * Der Wizard hat die Aufgabe ein neues Game zu erstellen. Dabei wird differenziert zwischen einem OfflineGame und einem LiveGame.
 * Diese Klasse verwaltet die einzelnen WizardPages.
 */
class NewGameWizard : public QWizard
{
    Q_OBJECT

public:
    explicit NewGameWizard(Storage *storage, QWidget *parent = 0);

    /**
     * WizardPages werden erstellt, Namen festgelegt
     */
    void initializeWidget();

    enum wizardWidgets {
        Page_LiveGameGeneralOptions,
        Page_LiveGameDokoOptions
    };

    Storage *storage() const;

private slots:
    void on_accepted();

private:
    NewGame::LiveGameGeneralOptionsWidget *m_liveGameGeneralOptionsWidget;
    NewGame::LiveDokoGameOptionsWidget *m_liveDokoGameOptionsWidget;

    Storage *m_storage;
};

}

#endif // NEWGAMEWIZARD_H

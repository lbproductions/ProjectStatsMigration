#ifndef LIVEGAMEGENERALOPTIONSWIDGET_H
#define LIVEGAMEGENERALOPTIONSWIDGET_H

#include <QWizardPage>

namespace Ui {
    class LiveGameGeneralOptionsWidget;
}

class Place;
class Player;
class PlacesComboBox;
class PlayersListWidget;

namespace Wizards {

class NewGameWizard;

namespace NewGame {

class LiveGameGeneralOptionsWidget : public QWizardPage
{
Q_OBJECT

public:
    explicit LiveGameGeneralOptionsWidget(NewGameWizard *parent);
    ~LiveGameGeneralOptionsWidget();

    void setupWidget();

    QString selectedType();

    int selectedPlayersCount();

    int nextId() const;

    bool isComplete() const;

    void saveOptions() const;

    QList<Player *> selectedPlayers();
    Place *selectedPlace();

private:
    Ui::LiveGameGeneralOptionsWidget *ui;
    PlacesComboBox* placesbox;
    NewGameWizard *m_wizard;

    PlayersListWidget *m_availablePlayersList;
    PlayersListWidget *m_chosenPlayersList;

    void generatePlayerPositions();
    QList<Player *> minimumPlayerConstellation();

private slots:
    void on_pushButtonDeselect_clicked();
    void on_pushButtonSelect_clicked();

    void on_pushButtonGeneratePositions_clicked();
    void on_pushButton_clicked();

    void on_chooseUnfinishedGamesDialogAccepted();
};

}
}

#endif // LIVEGAMEGENERALOPTIONSWIDGET_H

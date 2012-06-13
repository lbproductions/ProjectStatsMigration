//#ifndef LIVEGAMEROUNDTABLE_H
//#define LIVEGAMEROUNDTABLE_H

//#include <QTableWidget>

//class Player;
//class Round;
//class LiveGame;

///**
//* Widget, das die einzelnen Runden eines DokoLiveGames anzeigt.
//*/
//class LiveGameRoundTable : public QTableWidget
//{
//    Q_OBJECT
//public:
//    /**
//    * Erstellt eine neue Instanz der LiveGameRoundTable für das übergebene DokoLiveGame. Dabei wird für jeden Spieler und zusätzlich für die Runden-Punkte eine neue Spalte hinzugefügt.
//    */
//    explicit LiveGameRoundTable(LiveGameWidget *parent = 0);

//    void setLiveGame(LiveGame *liveGame);

//protected slots:
//    /**
//    * Markiert das HeaderItem des aktuellen Cardmixers durch einen farbigen Hintergrund
//    */
//    void markCardMixer();

//    void addCurrentRound();

//    /**
//    * Fügt zur Tabelle eine neue Runde hinzu. Für diese wird eine neue Reihe erstellt und mit den Daten aus der Runde befüllt.
//    */
//    virtual void addRound(::Database::Round *round);

//    void resizeEvent(QResizeEvent *event);

//protected:
//    LiveGame *m_livegame;

//    void fillWidget();
//};

//#endif // LIVEGAMEROUNDTABLE_H

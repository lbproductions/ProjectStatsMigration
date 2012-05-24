#ifndef LIVEGAMEPLAYERPOINTSGRAPH_H
#define LIVEGAMEPLAYERPOINTSGRAPH_H

#include "graph.h"

class LiveGame;
class Player;
class Round;

namespace Gui
{

namespace Graphs
{

namespace Items
{

class LiveGameCoordinateSystem;

//! Stellt einen Graphen für die Punktzahl eines Spieler beim LiveGame dar.
/*!
  Dafür werden zunächst Punkt für jede bestehende Runde hinzugefügt.<br>
  Anschließend wird das Spiel beobachtet und beim Beenden einer Runde ein neuer Punkt erstellt.
  */
class LiveGamePlayerPointsGraph : public Graph
{
    Q_OBJECT
public:
    /*!
      Erstellt einen Graphen, der die Punkte des Spielers \p player im Spiel \p liveGame im Koordinaten \p coordinateSystem darstellt.
      */
    LiveGamePlayerPointsGraph(Player *player, LiveGame *liveGame, LiveGameCoordinateSystem *coordinateSystem);

    /*!
      MUSS(!) aufgerufen werden, wenn eine neues Instanz dieses Objekts erstellt wird.
      */
    void setupGraph();

    Player* player();

public slots:
    /*!
      Dieser Slot wird aufgerufen, wenn im Spiel eine Runde beendet wird. Dann wird die Punktzahl des Spielers berechnet und als Punkt hinzugefügt.
      */
    virtual void addRound(Round*);

protected:
    /*!
      Liest die bestehenden Runden ein und fügt die Punkte daraus hinzu.
      */
    void readPlayerPoints();

    Player *m_player; //!< Der Spieler, den dieser Graph anzeigt.
    LiveGame *m_liveGame; //!< Das LiveGame dessen Punkte angezeigt werden.
    int m_totalPoints; //!< Wird gebraucht, um die Gesamtpunktzahl des Spielers zu speichern.
};

}
}
}

#endif // LIVEGAMEPLAYERPOINTSGRAPH_H

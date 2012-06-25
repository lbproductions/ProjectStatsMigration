#ifndef ADDDRINKWIDGET_H
#define ADDDRINKWIDGET_H

#include <QDialog>
#include <QPointer>

class Storage;

namespace LiveGameWindowNS {

/**
* Widget zum Hinzufügen von Drinks zu einem LiveGame.
*/
class AddDrinkWidget : public QDialog
{
    Q_OBJECT

public:
    /**
    * Erstellt eine neue Instanz des AddDrinkWidgets für das übergebene LiveGame. Dieses wird dabei mit den Playern des Spiels und den existierenden Drinks befüllt.
    */
    explicit AddDrinkWidget(Storage *storage, QWidget *parent = 0);
};

}

#endif // ADDDRINKWIDGET_H

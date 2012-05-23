#ifndef PLACESCOMBOBOX_H
#define PLACESCOMBOBOX_H

#include <QComboBox>
#include <QPointer>

class Place;
class PlacesContext;

class PlacesComboBox : public QComboBox
{
    Q_OBJECT

public:
    PlacesComboBox(PlacesContext *context, QWidget *parent = 0);

    Place *currentPlace() const;

public slots:
    void setCurrentPlace(Place *place);

signals:
    void currentIndexChanged(Place*);

private slots:
    void updateView();
    void on_currentIndexChanged();

private:
    QList<int> m_placePositions;
    PlacesContext *m_context;
};

#endif // PLACESCOMBOBOX_H

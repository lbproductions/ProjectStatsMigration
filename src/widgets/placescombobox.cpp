#include "placescombobox.h"

#include "../model/place.h"
#include "../model/projectstatsstorage.h"

PlacesComboBox::PlacesComboBox(PlacesContext *context, QWidget *parent) :
    QComboBox(parent),
    m_context(context)
{
    connect(this,SIGNAL(currentIndexChanged(int)),this,SLOT(on_currentIndexChanged()));

    updateView();
}

void PlacesComboBox::updateView()
{
    this->clear();
    m_placePositions.clear();

    foreach(Place *place, m_context->places()) {
        m_placePositions.append(place->id());
        addItem(place->displayName());
    }
}

void PlacesComboBox::on_currentIndexChanged()
{
    emit currentIndexChanged(currentPlace());
}

void PlacesComboBox::setCurrentPlace(Place *place)
{
    int index = m_placePositions.indexOf(place->id());
    setCurrentIndex(index);
}

Place *PlacesComboBox::currentPlace() const
{
    int index = currentIndex();

    if(index < 0 || index >= m_placePositions.count())
        return 0;

    int placeId = m_placePositions.at(index);
    return m_context->place(placeId);
}

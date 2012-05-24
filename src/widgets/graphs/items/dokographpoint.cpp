#include "dokographpoint.h"

#include "dokolivegameplayerpointsgraph.h"
#include "dokolivegamecoordinatesystem.h"

#include <model/doppelkopfround.h>
#include <model/player.h>
#include <model/schmeisserei.h>

#include <QPainter>

using namespace Gui::Graphs::Items;

DokoGraphPoint::DokoGraphPoint(QPoint point, DokoLiveGamePlayerPointsGraph* graph, DoppelkopfRound* r):
    GraphPoint(point,graph)
{
    m_radius = 7;
    m_dokoRound = r;
    m_player = graph->player();

    QString tooltip = "<h1>"+m_player->name()+"</h1>"+
            "<span style=\"font-size: 18pt;\">"+tr("Round")+" "+QString::number(r->number()+1)+"<br></span>"
            "<span style=\"font-size: 22pt;\">"
            "<b>"+tr("Points")+":</b> "+QString::number(r->points(m_player))+"<br>"+
            "<b>"+tr("Total")+":</b> "+QString::number(point.y())+"<br>"+
            "<br>";
    if (m_dokoRound->hochzeitPlayer() == m_player){
        tooltip += "Hochzeit<br>";
    }
    if (m_dokoRound->dokoSoloPlayer() == m_player){
        tooltip += m_dokoRound->doko_soloType()+"-Solo<br>";
    }
    if (m_dokoRound->trumpfabgabePlayer() == m_player){
        tooltip+= "Trumpfabgabe<br>";
    }
    if (m_dokoRound->schweinereiPlayer() == m_player){
        tooltip+= "Schweinerei<br>";
    }

    bool hasSchmeisserei = false;
    foreach(Schmeisserei* s, m_dokoRound->schmeissereienPerRound()) {
        if(s->player() == m_player)
            hasSchmeisserei = true;
    }

    if (hasSchmeisserei){
        tooltip+= "Schmeisserei<br>";
    }
    tooltip+="</span>";
    setToolTip(tooltip);
}

DoppelkopfRound* DokoGraphPoint::round() const
{
    return m_dokoRound;
}

void DokoGraphPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/)
{
    painter->setPen(QColor(255,255,255));
    painter->setPen(m_player->color());
    painter->setBrush(Qt::black);
    painter->drawEllipse(QPointF(  m_point.x()*m_graph->coordinateSystem()->xScale(),
                                    -m_point.y()*m_graph->coordinateSystem()->yScale()),
                                    m_radius,
                                    m_radius);
    painter->setPen(QColor("white"));
    QFont font = painter->font();
    font.setPointSize(10);
    painter->setFont(font);

    QString text;
    if (m_dokoRound->dokoSoloPlayer() == m_player){
        text = "S";
    }
    else if(m_dokoRound->hochzeitPlayer() == m_player){
        text = "H";
    }
    else if(m_dokoRound->trumpfabgabePlayer() == m_player){
        text = "T";
    }
    else if(m_dokoRound->rePlayer1() == m_player || m_dokoRound->rePlayer2() == m_player){
        text = "R";
    }
//TODO: wenn round->currentPlayingPlayers implementiert ist anpassen:
//    else if (m_dokoRound->currentplayingplayers.contains(player)){
//        text = "C";
//    }
    else{
        text = "-";
    }

    painter->drawText(QPointF(  (m_point.x()*m_graph->coordinateSystem()->xScale())-3,
                              (-m_point.y()*m_graph->coordinateSystem()->yScale())+3),text);
}

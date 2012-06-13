#include "graphpoint.h"

#include "coordinatesystem.h"
#include "graph.h"
#include "../graphview.h"

#include <QStaticText>
#include <QGraphicsSceneMouseEvent>

using namespace Gui::Graphs::Items;

GraphPoint::GraphPoint(QPoint point, Graph* graph) :
    AbstractItem(graph),
    m_graph(graph),
    m_point(point),
    m_radius(3),
    m_mouseIn(false)
{
    m_pen = QPen();
    m_pen.setBrush(QBrush(m_pen.color()));
    setAcceptHoverEvents(true);
}

QPoint GraphPoint::point() const
{
    return m_point;
}

void GraphPoint::setPoint(const QPoint& point)
{
    m_point = point;
    m_graph->updateDimensions(point);
}

QRectF GraphPoint::boundingRect() const
{
    return QRectF(  m_point.x() * m_graph->coordinateSystem()->xScale() - m_radius,
		    -m_point.y() * m_graph->coordinateSystem()->yScale() - m_radius,
		    m_radius*2,
		    m_radius*2);
}

void GraphPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/)
{
    if(m_mouseIn)
        m_radius += 3;
    painter->setPen(m_pen);
    painter->drawEllipse(QPointF(  m_point.x()*m_graph->coordinateSystem()->xScale(),
				    -m_point.y()*m_graph->coordinateSystem()->yScale()),
				    m_radius,
                         m_radius);
    if(m_mouseIn)
        m_radius -= 3;
}

void GraphPoint::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event)
    m_mouseIn = true;
    m_graph->scene()->invalidate();
}

void GraphPoint::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event)
    m_mouseIn = false;
    m_graph->scene()->invalidate();
}

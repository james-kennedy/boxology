/* See LICENSE file for copyright and license details. */

#include "graphicsbezieredge.hpp"
#include <QPoint>
#include <utility>
#include <algorithm>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsDropShadowEffect>
#include <iostream>
#include <QMetaProperty>
#include <QDebug>


#include "graphicsnodescene.hpp"
#include "graphicsnode.hpp"
#include "graphicsnodesocket.hpp"

using namespace std;

GraphicsDirectedEdge::GraphicsDirectedEdge(QPoint start, QPoint stop, qreal factor)
    :_pen(QColor("#00FF00"))
    , _effect(new QGraphicsDropShadowEffect())
    , _start(start)
    , _stop(stop)
      , _factor(factor)
{
    _pen.setWidth(2);
    setZValue(-1);

    _effect->setBlurRadius(15.0);
    _effect->setColor(QColor("#99050505"));
    setGraphicsEffect(_effect);
}

GraphicsDirectedEdge::GraphicsDirectedEdge(qreal factor) : GraphicsDirectedEdge(QPoint(0, 0), QPoint(0, 0), factor) {}


GraphicsDirectedEdge::
~GraphicsDirectedEdge()
{
    delete _effect;
}


void GraphicsDirectedEdge::
mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsPathItem::mousePressEvent(event);
}


void GraphicsDirectedEdge::
set_start(int x0, int y0)
{
    set_start(QPoint(x0, y0));
}


void GraphicsDirectedEdge::
set_stop(int x1, int y1)
{
    set_stop(QPoint(x1, y1));
}


void GraphicsDirectedEdge::
set_start(QPointF p)
{
    set_start(p.toPoint());
}


void GraphicsDirectedEdge::
set_stop(QPointF p)
{
    set_stop(p.toPoint());
}


void GraphicsDirectedEdge::
set_start(QPoint p)
{
    _start = p;
    this->update_path();
}


void GraphicsDirectedEdge::
set_stop(QPoint p)
{
    _stop = p;
    update_path();
}

void GraphicsDirectedEdge::
connect(shared_ptr<GraphicsNode> n1, ConstPortPtr source, 
        shared_ptr<GraphicsNode> n2, ConstPortPtr sink)
{

    connect_source(n1->connect_source(source, this));
    _sink = n2->connect_sink(sink, this);

}

void GraphicsDirectedEdge::
disconnect()
{
    if (_source) {
        _source->set_edge(nullptr);
    }
    if (_sink) _sink->set_edge(nullptr);
}


void GraphicsDirectedEdge::
disconnect_sink()
{
    if (_sink) _sink->set_edge(nullptr);
}

void GraphicsDirectedEdge::
disconnect_source()
{
    if (_source) _source->set_edge(nullptr);
}


void GraphicsDirectedEdge::
connect_sink(GraphicsNodeSocket *sink)
{
    if (_sink) _sink->set_edge(nullptr);
    _sink = sink;
    if (_sink) _sink->set_edge(this);
}

void GraphicsDirectedEdge::connect_source(GraphicsNodeSocket *source)
{
    if (_source) _source->set_edge(nullptr);
    _source = source;
    if (_source) _source->set_edge(this);
}

void GraphicsBezierEdge::
update_path()
{
    QPoint c1, c2;
    QPainterPath path(_start);

    // compute anchor point offsets
    const qreal min_dist = 0.f;
    // const qreal max_dist = 250.f;
    qreal dist = 0;
    if (_start.x() <= _stop.x()) {
        dist = std::max(min_dist, (_stop.x() - _start.x()) * _factor);
    } else {
        dist = std::max(min_dist, (_start.x() - _stop.x()) * _factor);
    }

    // dist = std::min(dist, max_dist);
    c1.setX(_start.x() + dist);
    c1.setY(_start.y());

    c2.setX(_stop.x() - dist);
    c2.setY(_stop.y());

    path.cubicTo(c1, c2, _stop);
    setPath(path);
}

void GraphicsBezierEdge::
paint(QPainter * painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/)
{
    painter->setPen(_pen);
    painter->drawPath(path());
}




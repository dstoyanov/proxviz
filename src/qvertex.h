/*
 * Copyright 2013 Dimo Stoyanov
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


/**
 *  @file graph.h
 *  @author Dimo Stoyanov
 *  @brief Definition of the vertex class.
 */
#ifndef QVERTEX_H
#define QVERTEX_H

#include <QGraphicsItem>
#include <QMouseEvent>
#include <boost/shared_ptr.hpp>


#include "graph.h"
#include "qedge.h"

class QEdge;
class Vertex;

class QVertex : public QGraphicsItem
{
public:
    QVertex(Vertex *v);

    ~QVertex();

    QRectF boundingRect() const;
    QPainterPath shape() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    void drawVertex(QPainter *painter);

    bool advance();

    void addEdge(boost::shared_ptr<QEdge> e);

    double size;

    void clearEdges();

    void addEdgesToScene();

    Vertex *graph_vertex;

    void fafa(QMouseEvent *event);



protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QGraphicsScene *parent;

    QPointF newPos;

    int selected;

    QColor color;
    QColor gradientColor;
    QBrush brush;

    QList<boost::shared_ptr<QEdge> > edgeList;


    void updateBrush();


};

#endif // QVERTEX_H

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

#ifndef QEDGE_H
#define QEDGE_H

#include "qvertex.h"

class QVertex;

class QEdge : public QGraphicsItem
{
public:
    QEdge(QVertex *sourceVertex, QVertex *destVertex);

    QVertex *sourcVertex() const;
    QVertex *destVertex() const;
    void draw(QPainter *painter);


    void adjust();

    enum { Type = UserType + 1};

    int type() const {return Type;}

    QVertex *source, *dest;
    QColor color;

protected:
    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

private:

    QGraphicsScene *parent;

    QPointF sourcePoint;
    QPointF destPoint;



};

#endif // QEDGE_H

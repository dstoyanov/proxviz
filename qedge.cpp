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

#include <QPainter>

#include "qedge.h"

QEdge::QEdge(QVertex *srcVertex, QVertex *dstVertex)
{
    setAcceptedMouseButtons(0);

    source = srcVertex;
    dest = dstVertex;

    boost::shared_ptr<QEdge> sp(this);

    source->addEdge(sp);
    dest->addEdge(sp);

    color = Qt::black;

    setZValue(0);
    adjust();
}

QVertex *QEdge::sourcVertex() const
{
    return source;
}

QVertex *QEdge::destVertex() const
{
    return dest;
}

void QEdge::adjust()
{
    if (!source || !dest || scene() == 0){
        return;
    }

    QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
    qreal length = line.length();

    prepareGeometryChange();

    if (length > qreal(source->size)) {

//        QPointF edgeOffset((line.dx() * 10) / length, (line.dy() * 10) / length);

        sourcePoint = line.p1();
        destPoint = line.p2();

    } else {
//        std::cout << "ADJUSTING EDGE " << length << " " << source->x() << " " << source->y() << "  "<< dest->x() << "  " << dest->y();
//        std::cout << source << "  " << dest << std::endl;
//        std::cout << "VERTEX " << source->graph_vertex->x << " " << source->graph_vertex->y << " " << dest->graph_vertex->x << "  " << dest->graph_vertex->y << std::endl;
        sourcePoint = destPoint = line.p1();
    }
}

QRectF QEdge::boundingRect() const
{
    if (!source || !dest)
        return QRectF();

    qreal penWidth = 1;
//    qreal extra = (penWidth + arrowSize) / 2.0;


    qreal extra = (penWidth) / 2.0;

    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                      destPoint.y() - sourcePoint.y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}


void QEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!source || !dest)
        return;

    QLineF line(sourcePoint, destPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;

    painter->setPen(QPen(color, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);


}

void QEdge::draw(QPainter *painter){
    painter->save();
    painter->drawLine(source->x(), source->y(), dest->x(), dest->y());
    painter->restore();

}

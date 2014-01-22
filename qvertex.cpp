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
#include <QGraphicsSceneMouseEvent>
#include <QStyleOption>
#include <QDebug>


#include "qvertex.h"

QVertex::QVertex( Vertex *v)
{

    graph_vertex = v;
//    this->size = v->size;
    this->size = 5;
    this->parent = parent;

    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);

    setZValue(1);

//    selected = false;

    selected = 0;

    color = Qt::red;
    gradientColor = Qt::darkRed;

    updateBrush();

}

QVertex::~QVertex(){
//    QList<QEdge *>::iterator i;

////    std::cout << "VERTEX DESTRUCTOR" << std::endl;

//    for(i = edgeList.begin(); i != edgeList.end(); ++i){
//////        std::cout << "TRYING TO REMOVE" << std::endl;

////        std::cout << "EDGE TYPE" << (*i)->Type << "general " << QEdge::Type << "  " << (*i) << " " << ((QEdge *)(*i))->source << "  " <<  ((QEdge *)(*i))->dest << std::endl;

//        if((*i) != NULL){
//            QGraphicsScene *s;
//            std::cout << "GETTING SCENE " << (*i) << std::endl;

////            qDebug() << (*i);
//            s = (*i)->scene();
////            std::cout << "SCENE" << std::endl;
//            s->removeItem(*i);

//            delete(*i);

//        } else{

////            std::cout << "NULL ITEM" << std::endl;
//        }
////        std::cout << "REMOVED" << std::endl;
//    }


    QList<boost::shared_ptr<QEdge> >::iterator i;
    for(i = edgeList.begin(); i != edgeList.end(); ++i){

        (*i)->hide();

        std::cout << (*i).get() << " " << (*i)->scene()<<std::endl;
        if((*i)->scene() != 0)
            (*i)->scene()->removeItem((*i).get());
//        (*i).reset();
        std::cout << "REMOVED" << std::endl;
    }

}

void QVertex::updateBrush(){
    QRadialGradient gradient(QPointF(size, size), size,
                             QPointF(size*0.5, size*0.5));

    gradient.setColorAt(0, color);
    gradient.setColorAt(1, gradientColor);
    brush = QBrush(gradient);
}

bool QVertex::advance()
{
    if (newPos == pos())
        return false;

    setPos(newPos);
    return true;
}

QPainterPath QVertex::shape() const
{
    QPainterPath path;
    path.addEllipse(-this->size / 2., -this->size / 2., this->size, this->size);

    return path;
}

QRectF QVertex::boundingRect() const
{
    qreal adjust = 2;

    return QRectF(-this->size / 2. - adjust, -this->size / 2. - adjust,
                  this->size + 3 * this->size / 20. + adjust,
                  this->size + 3 * this->size / 20. + adjust);
}


void QVertex::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
//    std::cout << "PAINT!!!!" << std::endl;

    painter->setRenderHint(QPainter::Antialiasing);

    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawEllipse(-7 * this->size / 20., -7 * this->size / 20., this->size, this->size);

    QRadialGradient gradient(-3, -3, 10);
    if (option->state & QStyle::State_Sunken) {
        gradient.setCenter(3, 3);
        gradient.setFocalPoint(3, 3);
        gradient.setColorAt(1, QColor(color).light(120));
        gradient.setColorAt(0, QColor(gradientColor).light(120));
    } else {
        gradient.setColorAt(0, color);
        gradient.setColorAt(1, gradientColor);
    }
    painter->setBrush(gradient);

    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-this->size / 2., -this->size / 2., this->size, this->size);
}

QVariant QVertex::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        foreach (boost::shared_ptr<QEdge> edge, edgeList)
            edge->adjust();

        break;
    default:
        break;
    }

    return QGraphicsItem::itemChange(change, value);
}

void QVertex::fafa(QMouseEvent *event)
{
//    if(selected){
//        color = Qt::red;
//        gradientColor = Qt::darkRed;
//        selected = false;
//    }else{
//        color = Qt::blue;
//        gradientColor = Qt::darkBlue;
//        selected = true;
//    }

    std::cout << "MOUSE PRESSED123" << std::endl;

    switch(selected){
    case 0:
        color = Qt::blue;
        gradientColor = Qt::darkBlue;
        selected++;
        break;
    case 1:
        color = Qt::green;
        gradientColor = Qt::darkGreen;
        selected++;
        break;
    case 2:
        color = Qt::yellow;
        gradientColor = Qt::darkYellow;
        selected++;
        break;
    default:
        color = Qt::red;
        gradientColor = Qt::darkRed;
        selected = 0;
    }

    updateBrush();
    update();
//    update();
//    QGraphicsItem::mousePressEvent(event);
}

void QVertex::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
    QPointF tmp = event->scenePos();
    std::cout << "VERTEX: " << graph_vertex->name << "  " << tmp.x() << "  " << tmp.y() << std::endl;

    graph_vertex->x = tmp.x();
    graph_vertex->y = tmp.y();
    setPos(tmp);
}


//void QVertex::addEdge(QEdge *edge)
//{
//    edgeList << edge;
//    edge->adjust();
//}

void QVertex::addEdge(boost::shared_ptr<QEdge> edge){
    edgeList << edge;
    edge->adjust();
}

void QVertex::clearEdges(){
    edgeList.clear();
}

void QVertex::addEdgesToScene(){
    QList<boost::shared_ptr<QEdge> >::iterator it;

    for(it = edgeList.begin(); it != edgeList.end(); ++it)
        if((*it)->scene() != parent)
            parent->addItem((*it).get());
}


void QVertex::drawVertex(QPainter *painter){

//    std::cout << "AGE: " << graph_vertex->age << std::endl;
    painter->save();
    painter->translate(pos().x() - size, pos().y() - size);
    painter->setBrush(brush);

//    if(graph_vertex != NULL)
//        painter->setOpacity(1 - graph_vertex->age / 4.);
    painter->drawEllipse(0, 0, int(2*size), int(2*size));
    painter->restore();

}

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


#include <QtGui>
#include <QtOpenGL>
#include <stdlib.h>

#include <math.h>
#include <iostream>

#include "glwidget.h"
#include "graphvizdatareader.h"

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{

    this->parent = parent;

    setAutoFillBackground(false);
    setMinimumSize(200, 200);

    scale = 1;
    translateX = 0;
    translateY = 0;

    fa2_timer.setSingleShot(false);
    connect(&fa2_timer, SIGNAL(timeout()), this, SLOT(updateLayout()));

    graph_update_timer.setSingleShot(false);
    connect(&graph_update_timer, SIGNAL(timeout()), this, SLOT(updateGraph()));

    fa2 = new ForceAtlas2(width(), height(), false);

    badge_graph = NULL;
    ubi_graph = NULL;

    ubi_radius =  1.5;

    default_reading_location = "../real-time-data/";

    src_mode = SRC_BADGE;

    ubi_scale = 40;
}

GLWidget::~GLWidget()
{
}



void GLWidget::initializeGL()
{
    glEnable(GL_MULTISAMPLE);

}

void GLWidget::mousePressEvent(QMouseEvent *event)
{


    QPoint mouse_position = event->pos() * painter_to_scene_transform.inverted();

//    cout << "MOUSE PRESSED" << mouse_position.x() << "  " << mouse_position.y() << endl;

    QImage img = grabFrameBuffer(true);
    img.save("screenshot.png", 0, 100);


    Graph *g = (src_mode == SRC_BADGE)? badge_graph : ubi_graph;
    std::pair<VertexIterator, VertexIterator> vi = g->getVertexIterators();

    for(; vi.first != vi.second; ++vi.first){
        Vertex *v = g->getVertex(vi.first);
//        QPoint v_point = g->getVertex(vi.first)->qvertex->pos();

        float distance = sqrt((v->x - mouse_position.x()) * (v->x - mouse_position.x()) +
                              (v->y - mouse_position.y()) * (v->y - mouse_position.y()));

        if(distance < v->size)
            v->qvertex->fafa(event);

//        float distance = sqrt((v->x() - mouse_position->x()) * (v->x() - mouse_position->x()) +
//                              (v->y() - mouse_position->y()) * (v->y() - mouse_position->y()));

//        if(distance < v->size){
//            v->mousePressEvent(event);
//        }

        setFocus();
    }
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{

    std::cout << "MOUSE MOVE \n";

    //    dx = event->x() - lastPos.x();
    //    dy = event->y() - lastPos.y();

    //    if (event->buttons() & Qt::LeftButton) {
    //        setXRotation(xRot + 8 * dy);
    //        setYRotation(yRot + 8 * dx);
    //    } else if (event->buttons() & Qt::RightButton) {
    //        setXRotation(xRot + 8 * dy);
    //        setZRotation(zRot + 8 * dx);
    //    }

    //    std::cout << "DX " << dx << " DY " << dy << std::endl;


    //    lastPos = event->pos();
}

void GLWidget::paintEvent(QPaintEvent *event)
{
    std::pair<VertexIterator, VertexIterator> vi;
    std::pair<EdgeIterator, EdgeIterator> ei;


    makeCurrent();
    glMatrixMode(GL_MODELVIEW);

    qglClearColor(Qt::white);
    glShadeModel(GL_FLAT);
    glEnable(GL_MULTISAMPLE);

    setupViewport(width(), height());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

//    int dx = viewCenterX + width() / 2;
//    int dy = viewCenterY + height() / 2;

    painter.translate(width() / 2 + translateX, height() / 2 + translateY);

    if(scale > 0)
        painter.scale(scale, scale);


    if((src_mode == SRC_BADGE && badge_graph) || (src_mode == SRC_UBI && ubi_graph)){
        Graph *graph;

        graph = (src_mode == SRC_BADGE) ? badge_graph : ubi_graph;
        float us = (src_mode == SRC_BADGE) ? 1 : ubi_scale;

        ei = graph->getEdgeIterators();
        for(;ei.first != ei.second; ++ei.first){
            Vertex *v1 = graph->getEdgeSource(ei.first);
            Vertex *v2 = graph->getEdgeTarget(ei.first);


            painter.drawLine(us * v1->x, us * v1->y, us * v2->x, us * v2->y);
        }

        vi = graph->getVertexIterators();
        for(; vi.first != vi.second; ++vi.first){
            Vertex *v = graph->getVertex(vi.first);

            if(v->qvertex == NULL){
                v->qvertex = new QVertex(v);
            }

            v->qvertex->setPos(us * v->x, us * v->y);
            v->qvertex->drawVertex(&painter);
        }

    } else if(src_mode == SRC_COMBINED && badge_graph != NULL && ubi_graph != NULL){

        ei = ubi_graph->getEdgeIterators();
        for(; ei.first != ei.second; ++ei.first){

            Vertex *v1 = ubi_graph->getEdgeSource(ei.first);
            Vertex *v2 = ubi_graph->getEdgeTarget(ei.first);

            try{
            badge_graph->checkEdgeExists(ubi_to_badge_map[v1->name], ubi_to_badge_map[v2->name]) ?
                        painter.setPen(Qt::green) : painter.setPen(Qt::blue);

            painter.drawLine(ubi_scale * v1->x, ubi_scale * v1->y, ubi_scale * v2->x, ubi_scale * v2->y);

            }catch(...){
                cout << "map key exception " << v1->name << "  " << v2->name << endl;
            }
        }

        ei = badge_graph->getEdgeIterators();
        for(; ei.first != ei.second; ++ei.first){
            string v1_badge =  badge_graph->getEdgeSource(ei.first)->name;
            string v2_badge =  badge_graph->getEdgeTarget(ei.first)->name;

            try{
                string v1_ubi = badge_to_ubi_map.at(v1_badge);
                string v2_ubi = badge_to_ubi_map.at(v2_badge);

                if(!ubi_graph->checkEdgeExists(v1_ubi, v2_ubi)){
                    Vertex *v1 = ubi_graph->getVertex(v1_ubi);
                    Vertex *v2 = ubi_graph->getVertex(v2_ubi);

                    if(v1 != NULL && v2 != NULL){
                        painter.setPen(Qt::darkCyan);
                        painter.drawLine(ubi_scale * v1->x, ubi_scale * v1->y, ubi_scale * v2->x, ubi_scale * v2->y);
                    }
                }
            }catch(...){
                cout << "map key exception " << v1_badge << "  " << v2_badge << endl;
            }\
        }

        painter.setPen(Qt::black);

        vi = ubi_graph->getVertexIterators();
        for(; vi.first != vi.second; ++vi.first){
            Vertex *v = ubi_graph->getVertex(vi.first);

            if(v->qvertex == NULL){
                v->qvertex = new QVertex(v);
            }


            v->qvertex->setPos(ubi_scale * v->x, ubi_scale * v->y);
            v->qvertex->drawVertex(&painter);
        }
    }

    painter_to_scene_transform = painter.transform();
    painter.end();




//    std::cout << "GRAPH DISPLAYED" << std::endl;
}

void GLWidget::resizeGL(int width, int height)
{
    setupViewport(width, height);
}

//void GLWidget::showEvent(QShowEvent *event)
//{
//    Q_UNUSED(event);
//}



void GLWidget::setupViewport(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef QT_OPENGL_ES
    glOrthof(0, 0, -0.5, 0.5, 4.0, 15.0);
#else
    glOrtho(0, 0 , -0.5, 0.5, 4.0, 15.0);
#endif

    glMatrixMode(GL_MODELVIEW);
}


void GLWidget::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
    case Qt::Key_Up:
        translateY += 2;
        break;

    case Qt::Key_Down:
        translateY -= 2;
        break;

    case Qt::Key_Left:
        translateX += 2;
        break;

    case Qt::Key_Right:
        translateX -= 2;
        break;

    case Qt::Key_S:
    {
        QImage img = grabFrameBuffer(true);
        img.save("screenshot.png", 0, 100);
        break;
    }

    case Qt::Key_O:
        scale += 0.5;
        break;
    case Qt::Key_P:
        scale -= 0.5;
        break;

    case Qt::Key_R:
        scale = 1;
        translateX = 0;
        translateY = 0;
        break;
    }

    update();
}

void GLWidget::initDataReaders(){
    boost::thread_group tgroup;
    QString dir_name;

    if(time_mode == REAL_TIME_MODE){

        dir_name = QString(default_reading_location.c_str());

    }else if (time_mode == RECORDED_MODE){
        dir_name = QFileDialog::getExistingDirectory
                (this, tr("Open Directory"), "",
                 QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    }

    QDir directory(dir_name);
    QStringList ubi_filter("*.log");
    QStringList ubisense_traces =  directory.entryList(ubi_filter);


    bdr =  new BadgeDataReader(dir_name.toStdString());

    if(ubisense_traces.size() != 1){
        std::cerr << "Unable to find Ubisense log" << std::endl;
        exit(1);
    }else{

        cout << "Ubisense file name: " << (dir_name + "/" + ubisense_traces.at(0)).toStdString() << endl;
        udr = new UbiDataReader((dir_name + "/" + ubisense_traces.at(0)).toStdString(), ubi_radius);
    }

    readUbiToBadgeMap((dir_name + "/dictionary.dat").toStdString());

    tgroup.create_thread(boost::bind(&DataReader::fillGraphBuffer, bdr));
    tgroup.create_thread(boost::bind(&DataReader::fillGraphBuffer, udr));

    sleep(150);

//    GraphVizDataReader *gdr = new GraphVizDataReader("/home/dstoyanov/hex.dot");
//    badge_graph = gdr->getSnapshot();

    badge_graph = bdr->getSnapshot();
    ubi_graph = udr->getSnapshot(0);

    cout << "UBIGRAPH EDGES: " << ubi_graph->getNumberEdges() << " TIMES: " << "  " << *badge_graph->getTime() << endl;
    if(*badge_graph->getTime() != *ubi_graph->getTime()){
        std::cerr << "Ubisense and Badge data streams are not synchronized" << std::endl;

        std::cerr << "Ubisense time " << *ubi_graph->getTime()
                  << " Badge Time " << *badge_graph->getTime() << std::endl;

        exit(1);
    }

    fa2->initializeAlgorithm(badge_graph);
    fa2->setDefaultCoefficients(badge_graph);

    std::cout << "FA2 initialized" << std::endl;

    for(int i = 0; i < 20; i++){
        fa2->randomize_layout(badge_graph);

        for(int j = 0; j < 100; j++)
            fa2->runAlgorithm(badge_graph);
    }

    fa2->print_execution_times("execution_times.txt");

    emit setSliderMax(bdr->getNumberSnapshots());

    emit setNumberEdgesLabel(badge_graph->getNumberEdges());
    emit setNumberVerticesLabel(badge_graph->getNumberVertices());
    emit setTimeLabel(badge_graph->getTime());

    update();
}

void GLWidget::setTimeMode(mode_type mode){
    time_mode = mode;

    initDataReaders();
    fa2_timer.start(1);

    if(time_mode == REAL_TIME_MODE)
        graph_update_timer.start(1000);
}


void GLWidget::updateLayout(){
    //TODO REMOVE!

    fa2->runAlgorithm(badge_graph);

    update();
}

void GLWidget::updateGraph(){
    Graph *tmp;
    Graph *tmp2;

    std::cout << "UPDATING GRAPH" << std::endl;

    ubi_graph = udr->getSnapshot();

    tmp2 = bdr->getSnapshot();
//    badge_graph->prepareNewGraph(tmp2);

//    badge_graph->printGraph();
//    std::cout << "************************************" << endl;
//    tmp2->printGraph();
//    exit(1);

    badge_graph = tmp2;

    fa2->initializeAlgorithm(badge_graph);
    fa2->randomize_layout(badge_graph);


    tmp = (src_mode == SRC_BADGE) ? badge_graph : ubi_graph;



   emit setNumberEdgesLabel(tmp->getNumberEdges());
   emit setNumberVerticesLabel(tmp->getNumberVertices());
   emit setTimeLabel(tmp->getTime());


    update();
}

void GLWidget::setSrcMode(int mode){
    switch(mode){
    case 0:
        src_mode = SRC_BADGE;
        fa2_timer.start(1);
        break;

    case 1:
        src_mode = SRC_UBI;
        fa2_timer.stop();
        break;

    case 2:
        src_mode = SRC_COMBINED;
        fa2_timer.stop();
        break;
    }

    setFocus();
    update();

}


void GLWidget::readUbiToBadgeMap(string filename){
    ifstream f(filename.c_str());
    string ubi_id;
    string badge_id;

    if(!f.is_open()){
        cerr << "Unable to read from " << filename << endl;
        exit(1);
    }

    while(f >> ubi_id >> badge_id){
        ubi_to_badge_map[ubi_id] = badge_id;
        badge_to_ubi_map[badge_id] = ubi_id;
    }
}

void GLWidget::sliderValueChanged(int v){
    Graph *tmp;

    badge_graph = bdr->getSnapshot(v);
    fa2->initializeAlgorithm(badge_graph);
    fa2->randomize_layout(badge_graph);

    ubi_graph = udr->getSnapshot(v);

    tmp = (src_mode == SRC_BADGE) ? badge_graph : ubi_graph;

    emit setSliderMax(bdr->getNumberSnapshots());
    emit setNumberEdgesLabel(tmp->getNumberEdges());
    emit setNumberVerticesLabel(tmp->getNumberVertices());
    emit setTimeLabel(tmp->getTime());

    setFocus();
    update();
}

void GLWidget::setUbiRadius(double r){

    udr->recomputeAllSnapshotVertices(r);

    if(src_mode == SRC_UBI){
        emit setNumberEdgesLabel(ubi_graph->getNumberEdges());
        emit setNumberVerticesLabel(ubi_graph->getNumberVertices());
    }


    update();
}

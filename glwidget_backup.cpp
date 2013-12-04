#include <QtGui>
#include <QtOpenGL>


#include "glwidget.h"
#include "qedge.h"

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    parent = parent;
    scale = 1;

    logo = new QtLogo(this);

    src_mode = SRC_BADGE;

    backgroundColor = QColor(Qt::white);

    graph_update_timer.setSingleShot(false);
    connect(&graph_update_timer, SIGNAL(timeout()), this, SLOT(updateGraph()));

    fa2_timer.setSingleShot(false);
    connect(&fa2_timer, SIGNAL(timeout()), this, SLOT(mainLoop()));

    graph = NULL;

    default_reading_location = "../real-time-data/";

    fa2 = new ForceAtlas2(width(), height());

    ubi_radius = 1.5;

    setAutoFillBackground(false);
}

GLWidget::~GLWidget()
{
}

//static void qNormalizeAngle(int &angle)
//{
//    while (angle < 0)
//        angle += 360 * 16;
//    while (angle > 360 * 16)
//        angle -= 360 * 16;
//}

void GLWidget::initDataReaders(){
    boost::thread_group tgroup;

    if(time_mode == REAL_TIME_MODE){

        bdr = new BadgeDataReader(default_reading_location);
        udr = new UbiDataReader(default_reading_location, 1373554279, ubi_radius);

    }else if (time_mode == RECORDED_MODE){
        QString dir_name = QFileDialog::getExistingDirectory
                (this, tr("Open Directory"), "",
                 QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

        QDir directory(dir_name);
        QStringList ubi_filter("*.log");
        QStringList ubisense_traces =  directory.entryList(ubi_filter);

        bdr =  new BadgeDataReader(dir_name.toStdString());
        udr = new UbiDataReader((dir_name + "/" + ubisense_traces.at(0)).toStdString(), 1373554965, ubi_radius);
    }

        tgroup.create_thread(boost::bind(&DataReader::fillGraphBuffer, bdr));
        tgroup.create_thread(boost::bind(&DataReader::fillGraphBuffer, udr));

        sleep(1);

        graph = bdr->getSnapshot();
        fa2->initializeAlgorithm(graph);
        fa2->setDefaultCoefficients(graph);
        fa2->randomize_layout(graph);

        update();

}

void GLWidget::initializeGL()
{
    glEnable(GL_MULTISAMPLE);

}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
//    lastPos = event->pos();

//    std::cout << "MOUSE PRESSED " << event->pos().x() << " " << event->pos().y() << std::endl;
//    scale /= 2;
//    std::cout << "SCALE " << scale << std::endl;
//    update();

}

void GLWidget::mouseMoveEvent(QMouseEvent *event){

}

void GLWidget::paintEvent(QPaintEvent *event)
{
    makeCurrent();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    qglClearColor(Qt::white);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_MULTISAMPLE);
    static GLfloat lightPosition[4] = { 0.5, 5.0, 7.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    setupViewport(width(), height());

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
//    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
//    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
//    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);

    logo->draw();

    glShadeModel(GL_FLAT);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

//    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing);
//    foreach (Bubble *bubble, bubbles) {
//        if (bubble->rect().intersects(event->rect()))
//            bubble->drawBubble(&painter);
//    }
//    drawInstructions(&painter);
//    painter.end();
}

//void GLWidget::paintEvent(QPaintEvent *event)
//{
//    makeCurrent();

//    std::pair<VertexIterator, VertexIterator> vi;
//    std::pair<EdgeIterator, EdgeIterator> ei;


////    std::cout << "PAINT EVENT\n";
////! [4]
////    glMatrixMode(GL_MODELVIEW);
////    glPushMatrix();
//////! [4]

//////! [6]
////    qglClearColor(backgroundColor);
////    glShadeModel(GL_SMOOTH);
//////    glEnable(GL_DEPTH_TEST);
//////    glEnable(GL_CULL_FACE);
//////    glEnable(GL_LIGHTING);
//////    glEnable(GL_LIGHT0);
////    glEnable(GL_MULTISAMPLE);
//////    static GLfloat lightPosition[4] = { 0.5, 5.0, 7.0, 1.0 };
//////    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

////    setupViewport(width(), height());
//////    std::cout << "VIEWPORT " << width() << " " << height() << std::endl;
//////! [6]

//////! [7]
////    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
////    glLoadIdentity();
////    glScalef(scale, scale, scale);
//////    glTranslatef(0.0, 0.0, -10.0);

////    glShadeModel(GL_FLAT);
////    glDisable(GL_CULL_FACE);
////    glDisable(GL_DEPTH_TEST);
////    glDisable(GL_LIGHTING);

////    glMatrixMode(GL_MODELVIEW);
////    glPopMatrix();



////    glPushMatrix();
////    glMatrixMode(GL_PROJECTION);
//    qglClearColor(backgroundColor);

//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glLoadIdentity();
////    glScalef(scale, scale, scale);

//    glTranslatef(-5, -5, 10);


//    std::vector<QVertex *>::iterator it;
//    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing);
////    foreach (Bubble *bubble, bubbles) {
////        if (bubble->rect().intersects(event->rect()))
////            bubble->drawBubble(&painter);
////    }
////    drawInstructions(&painter);
////    bubble->drawBubble(&painter);
////    vertex->drawVertex(&painter);

////    for(it = vertices.begin(); it != vertices.end(); ++it){
////        (*it)->drawVertex(&painter);
////    }
////    painter.end();

////    glPopMatrix();
////    std::cout << "CHECKING GRAPH" << std::endl;

//    //    if(graph){
//////        std::cout << "DISPLAYING GRAPH" << std::endl;
////        vi = graph->getVertexIterators();
////        for(;vi.first != vi.second; ++vi.first){
////            Vertex *v = graph->getVertex(vi.first);

////            if(v->qvertex == NULL){
////                v->qvertex = new QVertex(v);
////            }

////            v->qvertex->setPos(v->x, v->y);
////            v->qvertex->drawVertex(&painter);
////        }

////        ei = graph->getEdgeIterators();
////        for(; ei.first != ei.second; ++ei.first){
////            Vertex *v1 = graph->getEdgeSource(ei.first);
////            Vertex *v2 = graph->getEdgeTarget(ei.first);

////            QEdge *e = new QEdge(v1->qvertex, v2->qvertex);
////            e->draw(&painter);
////        }

////        painter.end();
////    }


//    painter.drawEllipse(-5, -5, 10, 10);
//    painter.drawEllipse(28, 0, 10, 10);
//    painter.end();

//}

void GLWidget::resizeGL(int width, int height)
{
    setupViewport(width, height);

}

void GLWidget::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
//    createBubbles(20 - bubbles.count());
//    vertex = new QVertex(NULL);
//    vertex->setPos(20, 20);
//    int num_vertices = 1000;

//    int w = this->width();
//    int h = this->height();


//    for(int i = 0; i < num_vertices; i++){
//        QVertex *v = new QVertex(NULL);
//        vertices.push_back(v);

//        int x =  (double) w * rand() / (double) RAND_MAX;
//        int y =  (double) h * rand() / (double) RAND_MAX;

//        v->setPos(x, y);
//    }
}
void GLWidget::setupViewport(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef QT_OPENGL_ES
    glOrthof(-0.5, +0.5, -0.5, 0.5, 4.0, 15.0);
#else
    glOrtho(-0.5, +0.5, -0.5, 0.5, 4.0, 15.0);
#endif
    glMatrixMode(GL_MODELVIEW);
}

//void GLWidget::setupViewport(int w, int h)
//{
//    int side = qMin(w, h);
////    glViewport((w - side) / 2, (h - side) / 2, side, side);
//    glViewport(0, 0, 10, 20);

//    std::cout << "WIDHT() " << width() << "  " << height() << endl;
//    std::cout << "SETTING VIEWPORT " << (w - side) / 2 << "  " << (h - side) / 2 << "  " << side << std::endl;
//    std::cout << "w: " << w << " h: " << h << endl;
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//#ifdef QT_OPENGL_ES
//    glOrthof(-0.5, +0.5, -0.5, 0.5, 4.0, 15.0);
//#else
////    glOrtho(0, 0, 0, 0, 4, 5);
//    std::cout << "HERE" << endl;
////    glOrtho(-0.5, +0.5, -0.5, 0.5, 4.0, 15.0);
////    glOrtho(-width / 2., width /2., -height / 2., height / 2., 4.0, 15.0);
//#endif
//    glMatrixMode(GL_MODELVIEW);
//}



void GLWidget::wheelEvent(QWheelEvent *e){
    std::cout << "WHEEL EVENT \n";
    e->delta() > 0 ? scale += scale*0.1f : scale -= scale*0.1f;

}

void GLWidget::mainLoop(){
//    std::cout << "MAIN LOOP" << std::endl;

//    while(true){
//    for(int i = 0; i < 100; i++){
        fa2->runAlgorithm(graph);

        update();
//    }
}

void GLWidget::updateGraph(){
    std::cout << "UPDATE GRAPH" << std::endl;

    if(src_mode == SRC_BADGE)
        graph = bdr->getSnapshot();
    else if(src_mode == SRC_UBI)
        graph = udr->getSnapshot();
    else if(src_mode == SRC_COMBINED)
        std::cout << "COMBINED SOURCE" << std::endl;
}


/*
    Called only once by the ModeWidget during the initialization
*/
void GLWidget::setTimeMode(mode_type mode){
    time_mode = mode;

    initDataReaders();


//    graph_update_timer.start(1000);
    fa2_timer.start(1);


}

void GLWidget::setSrcMode(data_src_type mode){
    std::cout << "SRC MODE \n";
    src_mode = mode;
}

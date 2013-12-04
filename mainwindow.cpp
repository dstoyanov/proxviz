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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qvertex.h"

#include <ulimit.h>

#include <unistd.h>
#include <QDebug>
#include <QtGui/QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    gl_widget = new GLWidget(this);
    ui->horizontalLayout->addWidget(gl_widget);
    gl_widget->setFocus();

    ui->ubiRangeSpinBox->setValue(1.5);

    connect(gl_widget, SIGNAL(setNumberEdgesLabel(int)),
            this, SLOT(setNumberEdges(int)));

    connect(gl_widget, SIGNAL(setNumberVerticesLabel(int)),
            this, SLOT(setNumberVertices(int)));

    connect(gl_widget, SIGNAL(setTimeLabel(time_t*)),
            this, SLOT(setTimeLabel(time_t*)));

    connect(gl_widget, SIGNAL(setSliderMax(int)), this, SLOT(setSliderMax(int)));

    connect(ui->sourceComboBox, SIGNAL(currentIndexChanged(int)),
            gl_widget, SLOT(setSrcMode(int)));

//    connect(ui->snapshotSlider, SIGNAL(valueChanged(int)),
//            gl_widget, SLOT(sliderValueChanged(int)));

    connect(ui->snapshotSlider, SIGNAL(valueChanged(int)),
            this, SLOT(sliderValueChanged(int)));

    connect(ui->snapshotSpinBox, SIGNAL(valueChanged(int)),
            this, SLOT(snapshotSpinBoxValueChanged(int)));


    connect(ui->ubiRangeSpinBox, SIGNAL(valueChanged(double)),
            this, SLOT(setUbiRadius(double)));

    //    connect(this, SIGNAL(keyPressEvent(QKeyEvent*)), gl_widget,
    //            SLOT(keyPressEvent(QKeyEvent*)));


    mode_dialog = new ModeDialog(this);
    connect(mode_dialog, SIGNAL(setMode(mode_type)), this,
            SLOT(setTimeMode(mode_type)));

    mode_dialog->show();
    mode_dialog->raise();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setTimeMode(mode_type mode){

    if(mode == RECORDED_MODE){
        ui->snapshotSlider->setEnabled(true);
        ui->snapshotSpinBox->setEnabled(true);

    }else if (mode == REAL_TIME_MODE){
        ui->snapshotSlider->setEnabled(false);
        ui->snapshotSpinBox->setEnabled(false);
    }

    gl_widget->setTimeMode(mode);
}

void MainWindow::setNumberEdges(int n){
    ui->numEdgesLabel->setText(QString::number(n));
}

void MainWindow::setNumberVertices(int n){
    ui->numVerticesLabel->setText(QString::number(n));
}

void MainWindow::setTimeLabel(time_t *t){
    char time_str[20];
    strftime(time_str, 20, "%Y-%m-%d %H:%M:%S", localtime(t));
    ui->timeLabel->setText(time_str);
}

void MainWindow::setSliderMax(int i){
    cout << "SETTING SLIDER MAX " << i << endl;
    ui->snapshotSlider->setMaximum(i);
    ui->numberSnapshotLabel->setText(QString::number(i));
}

void MainWindow::setUbiRadius(double r){
    if(r > 0){
        gl_widget->setUbiRadius(r);
    }else{
        ui->ubiRangeSpinBox->setValue(0.1);
    }
}


void MainWindow::sliderValueChanged(int v){
    ui->snapshotSpinBox->setValue(v);
    gl_widget->sliderValueChanged(v);
}

void MainWindow::snapshotSpinBoxValueChanged(int v){
    int max = ui->snapshotSlider->maximum();
    int min = ui->snapshotSlider->minimum();

    if(v < max && v > min){
        ui->snapshotSlider->setValue(v);
        gl_widget->sliderValueChanged(v);
    }else if(v > max){
        ui->snapshotSpinBox->setValue(max);
    }else if(v < min){
        ui->snapshotSpinBox->setValue(min);
    }

}

//void MainWindow::keyPressEvent(QKeyEvent *e){
//    if(e->key() == Qt::Key_Up){
//        cout << "UP ARROW" << endl;
//    }
//}


/*
void MainWindow::displayRandom(){

    int num_vertices = 100000;
    int edges_per_node = 20;



    double w =  ui->graphViewer->width();
    double h = ui->graphViewer->height();

    std::vector<QVertex*> vertices;
    std::vector<QVertex*>::iterator it;

    for(int i = 0; i < num_vertices; i++){
        QVertex *v = new QVertex(this->scene, NULL);
        scene->addItem(v);
        vertices.push_back(v);

        int x = (double) w / 2. - (double) w * rand() / (double) RAND_MAX;
        int y = (double) h / 2. - (double) h * rand() / (double) RAND_MAX;

        v->setPos(x, y);
    }

    cout << "QEDGE " << sizeof(QEdge) << " " << sizeof(QEdge*) << endl;
    cout << "QVERTEX" << sizeof(QVertex) << endl;

    for(it = vertices.begin(); it != vertices.end(); ++it){
        for(int i = 0; i < edges_per_node; i++){
            int v = num_vertices / 2 - num_vertices * rand() / RAND_MAX;
            QEdge *e = new QEdge(scene, *it, vertices[v]);
            scene->addItem(e);
        }
    }
    cout << "DISPLAY DONE" << endl;
}



void MainWindow::displayGraph(){

    std::pair<VertexIterator, VertexIterator> iterators;
    std::pair<EdgeIterator, EdgeIterator> e_iterators;

    iterators = graph->getVertexIterators();

    cout << "DISPLAY GRAPH\n";

    for(; iterators.first != iterators.second; ++iterators.first){
        Vertex *v = graph->getVertex(iterators.first);

        if(v->qvertex == NULL){
            v->qvertex = new QVertex(this->scene, v);
            scene->addItem(v->qvertex);
        }else if (graph->graph_state == VERTICES_REMOVED){
            scene->addItem(v->qvertex);
            v->qvertex->addEdgesToScene();
        }

        v->qvertex->setPos(v->x, v->y);

        v->qvertex->setOpacity( 1 - v->age / 4.);

    }

    cout << "VERTICES DISPLAYED\n";

//    if(!graph->first_display){
    if(graph->graph_state == NOT_SHOWN){
        e_iterators = graph->getEdgeIterators();

        for(; e_iterators.first != e_iterators.second; ++e_iterators.first){
            Vertex *v1 = graph->getEdgeSource(e_iterators.first);
            Vertex *v2 = graph->getEdgeTarget(e_iterators.first);

            QEdge * e = new QEdge(scene, v1->qvertex, v2->qvertex);
            scene->addItem(e);

        }

//        graph->first_display = true;

    }

    cout << "EDGES DISPLAYED\n";

//    else if (graph->graph_state == VERTICES_REMOVED){
//        e_iterators = graph->getEdgeIterators();

//        for(; e_iterators.first != e_iterators.second; ++e_iterators.first){

//            scene->addItem();
//        }

//    }


    graph->graph_state = SHOWN;
    scene->update();

    //    ui->numEdgesLabel->setText(QString(graph->getNumberEdges()));
    ui->numEdgesLabel->setText(QString::number(graph->getNumberEdges()));
    ui->numVerticesLabel->setText(QString::number(graph->getNumberVertices()));

    char time_str[20];
    strftime(time_str, 20, "%Y-%m-%d %H:%M:%S", localtime(graph->getTime()));
    ui->timeLabel->setText(time_str);

    cout << "END DISPLAY\n";

}

void MainWindow::mousePressEvent(QMouseEvent *e){

    //    timer.start(100, this);

    //    this->scene->setSceneRect(-this->scene_width / 2.,
    //                              -this->scene_height / 2.,
    //                              this->scene_width,
    //                              this->scene_height);

    //    QVertex *v = new QVertex(scene, 10);
    //    this->scene->addItem(v);

    //    v->setPos(0, 0);

    //    cout << "scene " << ui->graphViewer->width() << " " << ui->graphViewer->height() << endl;

    //    scene->clear();

    //    scene->clear();


}

void MainWindow::keyPressEvent(QKeyEvent *e){
    switch(e->key()){

    case Qt::Key_P:
        if(graph_update_timer.isActive())
            graph_update_timer.stop();
        else
            graph_update_timer.start(1000, this);

        break;

    case Qt::Key_O:
        if(fa_timer.isActive())
            fa_timer.stop();
        else
            fa_timer.start(10, this);
        break;

    case Qt::Key_S:
        QPixmap pixmap = QPixmap::grabWidget(ui->graphViewer);
        pixmap.save("screenshot.png", 0, 100);
        break;

    }
}



void MainWindow::timerEvent(QTimerEvent *e){
//    if(passed_time == 1000){
//        scene->clearFocus();
//        QPixmap pixmap = QPixmap::grabWidget(ui->graphViewer);
//        pixmap.save("screenshot_1second.png", 0, 100);
//    }

    if(e->timerId() == fa_timer.timerId() && ui->sourceComboBox->currentText() == "badges"){
//        if(passed_time == 1){
//            QPixmap pixmap = QPixmap::grabWidget(ui->graphViewer);
//            pixmap.save("screenshot_random.png", 0, 100);
//        }
        fa->runAlgorithm(graph);

        displayGraph();


        passed_time++;

    }else if(e->timerId() == fa_timer.timerId() && ui->sourceComboBox->currentText() == "badges"){
        displayGraph();

    } else if(e->timerId() == graph_update_timer.timerId() && mode == REAL_TIME_MODE){
        if(ui->sourceComboBox->currentText() == "badges")
            old_graph = bdr->getSnapshot();
        else if(ui->sourceComboBox->currentText() == "ubisense")
            old_graph = udr->getSnapshot();

        exit(1);
        graph->prepareNewGraph(old_graph, scene);


        graph = old_graph;

        displayGraph();

    }
}

void MainWindow::setUbiRange(double r){
    udr->setRange(r);
}

void MainWindow::moveSlider(int v){
    current_snapshot = v;

    QList<QGraphicsItem *> scene_items = scene->items();
    QList<QGraphicsItem *>::iterator item_it;

    for(item_it = scene_items.begin(); item_it != scene_items.end(); ++item_it)
        scene->removeItem(*item_it);

    graph->graph_state = VERTICES_REMOVED;

    ui->snapshotSpinBox->setValue(v);

    if(ui->sourceComboBox->currentText() == "badges"){
        graph = bdr->getSnapshot(v);
        fa->initializeAlgorithm(graph);
        fa->setDefaultCoefficients(graph);
        fa->randomize_layout(graph);

    }else if(ui->sourceComboBox->currentText() == "ubisense"){
        graph = udr->getSnapshot(v);

        cout << "NUMBER EDGES: " << graph->getNumberVertices() << endl;

        displayGraph();

    }else if(ui->sourceComboBox->currentText() == "combined"){
        Graph *tmp_graph = bdr->getSnapshot(v);
        graph = udr->getSnapshot(v);
    }

}

void MainWindow::spinboxChanged(int v){
    ui->snapshotSlider->setValue(v);
}

void MainWindow::setMode(mode_type mode){
    mode = mode;

    boost::thread_group tgroup;


    if(mode == REAL_TIME_MODE){

        ui->snapshotSlider->setEnabled(false);
        ui->snapshotSpinBox->setEnabled(false);

        bdr =  new BadgeDataReader("../../data/badge_data/");

        udr = new UbiDataReader("../../workspace/ubisense/ubisense_shared/experiment11.07_data/"
                                "ubisense/ubisense_traces/ubisense_trace.log", 1373554279, 1.5);
        graph_update_timer.start(1000, this);


    } else if(mode == RECORDED_MODE){
        QString dir_name = QFileDialog::getExistingDirectory
                (this, tr("Open Directory"), "",
                 QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

        QDir directory(dir_name);
        QStringList ubi_filter("*.log");
        QStringList ubisense_traces =  directory.entryList(ubi_filter);

//        if(ubisense_traces.length() < 1){
//            cerr << "No Ubisense log file in " << dir_name.toStdString();
//            exit(1);
//        }


        bdr =  new BadgeDataReader(dir_name.toStdString());

//        udr = new UbiDataReader((dir_name + "/" + ubisense_traces.at(0)).toStdString(), 1373554965, 1.5);
    }

//    tgroup.create_thread(boost::bind(&DataReader::fillGraphBuffer, bdr));
//    tgroup.create_thread(boost::bind(&DataReader::fillGraphBuffer, udr));
    bdr->readGraph();


//    sleep(1);
//    cout << "GETTING SNAPSHOT" << endl;
    graph = bdr->getSnapshot();

    cout << "GRAPH " << graph->getNumberEdges() << "  " << graph->getNumberVertices() << endl;
//    exit(1);

    fa = new ForceAtlas2(scene->width(), scene->height());


    fa->initializeAlgorithm(graph);


    fa->setDefaultCoefficients(graph);

    fa->randomize_layout(graph);

    cout << "GRAPH RANDOMIZED\n";

    this->raise();
    displayGraph();


    int num_snapshots = bdr->getNumberSnapshots();

    ui->snapshotSlider->setMinimum(0);
    ui->snapshotSlider->setMaximum(num_snapshots);
    ui->numberSnapshotLabel->setText(QString::number(num_snapshots));

    fa_timer.start(1, this);
    graph_update_timer.start(1000, this);

}

*/

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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QBasicTimer>
#include <QKeyEvent>

#include "graph.h"
#include "badgedatareader.h"
#include "ubidatareader.h"
#include "forceatlas2.h"
#include "glwidget.h"

#include "graphvizdatareader.h"

#include "modedialog.h"



namespace Ui {
class MainWindow;
}

class GLWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);


    ~MainWindow();


public slots:
    void setTimeMode(mode_type);
    void setNumberEdges(int n);
    void setNumberVertices(int n);
    void setTimeLabel(time_t *t);
    void setSliderMax(int i);
    void setUbiRadius(double r);
    void sliderValueChanged(int v);
    void snapshotSpinBoxValueChanged(int v);

private:
    Ui::MainWindow *ui;

//    QGraphicsScene *scene;

    ModeDialog *mode_dialog;
    GLWidget *gl_widget;

    mode_type mode;

//    Graph *graph;
//    Graph *old_graph;

//    double scene_width;
//    double scene_height;

//    void displayGraph();


//    BadgeDataReader *bdr;
//    UbiDataReader *udr;

//    GraphVizDataReader *gvdr;

//    boost::thread *bdr_thread;

//    ForceAtlas2 *fa;

//    QBasicTimer fa_timer;
//    QBasicTimer graph_update_timer;

//    bool graph_updated;

//    QList<QEdge *> edges;

//    int current_snapshot;

//    int passed_time;

//    void displayRandom();



protected:
//    void mousePressEvent ( QMouseEvent *e);
////    void mouseReleaseEvent(QMouseEvent *e);
//    void timerEvent(QTimerEvent *e);
//    void keyPressEvent( QKeyEvent *e);

//private slots:
//    void setUbiRange(double r);
//    void moveSlider(int v);
//    void spinboxChanged(int v);


//    void setMode(mode_type mode);



};

#endif // MAINWINDOW_H
